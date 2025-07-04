#include "HotkeyManager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <fmt/core.h>
#include <iostream>
#include "ConfigManager.h"

class Window
{
public:
    Window(const char *title, int w, int h, Uint32 flags)
    {
        window = SDL_CreateWindow(title, w, h, flags);
        if (!window)
        {
            fmt::print("Window creation failed: {}\n", SDL_GetError());
        }
    }

    ~Window()
    {
        if (window)
        {
            SDL_DestroyWindow(window);
            fmt::print("SDL_Window  Destroy :\n");
        }
    }

    operator SDL_Window *() { return window; }
    operator bool() const { return window != nullptr; }

private:
    SDL_Window *window;
};

int main(int argc, char *argv[])
{
    // Вывод версии SDL с использованием правильных макросов
    const int compiled = SDL_VERSION;    /* hardcoded number from SDL headers */
    const int linked = SDL_GetVersion(); /* reported by linked SDL library */

    fmt::print("SDL version: {}.{}.{}\n",
               SDL_VERSIONNUM_MAJOR(compiled),
               SDL_VERSIONNUM_MINOR(compiled),
               SDL_VERSIONNUM_MICRO(compiled));

    fmt::print("SDL version: {}.{}.{}\n",
               SDL_GetKeyName(SDLK_ESCAPE),
               SDL_VERSIONNUM_MINOR(compiled),
               SDL_VERSIONNUM_MICRO(compiled));

    SDL_Log("We compiled against SDL version %d.%d.%d ...\n",
            SDL_VERSIONNUM_MAJOR(compiled),
            SDL_VERSIONNUM_MINOR(compiled),
            SDL_VERSIONNUM_MICRO(compiled));

    fmt::print("Starting SDL3 Input Manager...\n");

    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        fmt::print("SDL initialization failed: {}\n", SDL_GetError());
        return 1;
    }

    // Создание окна

    Window window("Input Manager Demo", 800, 600, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        fmt::print("Window creation failed: {}\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    HotkeyManager mng;
    bool running = true;

    // Создаем карту действий
    ConfigManager::ActionMap actions =
        {
            {"save", []()
             { fmt::print("Ctrl+S pressed! Saving document...\n"); }},
            {"quit", [&running]()
             {
                 fmt::print("ESC pressed! Close...\n");
                 running = false;
             }},
            {"special", []()
             { fmt::print("Ctrl+Shift+Left Click pressed!\n"); }}};

    // Загрузка конфигурации из файла
    if (!ConfigManager::load_config("config.json", mng, actions))
    {
        fmt::print("Using default hotkeys\n");

        // Регистрация горячих клавиш по умолчанию
      /*  mng.register_hotkey(SDLK_S, SDL_KMOD_CTRL, actions["save"]);
        mng.register_hotkey(SDLK_ESCAPE, SDL_KMOD_NONE, actions["quit"]);
        mng.register_mouse_hotkey(SDL_BUTTON_LEFT,
                                  SDL_KMOD_CTRL | SDL_KMOD_SHIFT,
                                  actions["special"]);*/
    }

    // Регистрация клавиатурных комбинаций
    // mng.register_hotkey(SDLK_S, SDL_KMOD_CTRL, []()
    //                    { fmt::print("Ctrl+S pressed! Saving document...\n"); });

    mng.register_hotkey(SDLK_F1, SDL_KMOD_NONE, []()
                        { fmt::print("F1 pressed! F1 help...\n"); });

    // Регистрация комбинаций с мышью
    mng.register_mouse_hotkey(SDL_BUTTON_LEFT, SDL_KMOD_CTRL, []()
                              { fmt::print("Ctrl+Left Click pressed!\n"); });

    // mng.register_mouse_hotkey(SDL_BUTTON_LEFT, SDL_KMOD_LCTRL | SDL_KMOD_LSHIFT, []()
    //                           { fmt::print("Ctrl+Shift+Left Click pressed!\n"); });

    mng.register_click_callback(SDL_BUTTON_RIGHT, []()
                                { fmt::print("Right button clicked!\n"); });

    // Регистрация обработчиков мыши
    // mng.registerMouseMoveCallback([](int x, int y)
    //                               { fmt::print("Mouse moved to: ({}, {})\n", x, y); });

    // mng.registerMouseWheelCallback([](float x, float y)
    //                               { fmt::print("Mouse wheel: X={:.2f}, Y={:.2f}\n", x, y); });

    // Главный цикл

    // mng.register_hotkey(SDLK_ESCAPE, SDL_KMOD_NONE, [&running]()
    //                     {
    //                             fmt::print("ESC pressed! Close...\n");
    //                             running = false; });
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            mng.handle_event(&event);
        }

        mng.update();
        SDL_Delay(16);
    }

    // Освобождение ресурсов

    SDL_Quit(); // Window автоматически уничтожится в стеке

    printf("Application terminated\n");

    return 0;
}