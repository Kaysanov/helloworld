#include "HotkeyManager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <fmt/core.h>
#include <iostream>

int main(int argc, char *argv[])
{
    // Вывод версии SDL с использованием правильных макросов
    const int compiled = SDL_VERSION;    /* hardcoded number from SDL headers */
    const int linked = SDL_GetVersion(); /* reported by linked SDL library */

    fmt::print("SDL version: {}.{}.{}\n",
               SDL_VERSIONNUM_MAJOR(compiled),
               SDL_VERSIONNUM_MINOR(compiled),
               SDL_VERSIONNUM_MICRO(compiled));

    SDL_Log("We compiled against SDL version %d.%d.%d ...\n",
            SDL_VERSIONNUM_MAJOR(compiled),
            SDL_VERSIONNUM_MINOR(compiled),
            SDL_VERSIONNUM_MICRO(compiled));

    printf("Starting SDL3 Input Manager...\n");

    // Инициализация SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        fmt::print("SDL initialization failed: {}\n", SDL_GetError());
        return 1;
    }

    // Создание окна
    SDL_Window *window = SDL_CreateWindow("Input Manager Demo",
                                          800, 600,
                                          SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        fmt::print("Window creation failed: {}\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    HotkeyManager input;

    // Регистрация клавиатурных комбинаций
    input.register_hotkey(SDLK_S, SDL_KMOD_CTRL, []()
                          { std::cout << "Ctrl+S pressed! Saving document...\n"; });

    input.register_hotkey(SDLK_F1, SDL_KMOD_NONE, []()
                          { std::cout << "Ctrl+F1 pressed! F1 help...\n"; });

    // Регистрация комбинаций с мышью
    input.register_mouse_hotkey(SDL_BUTTON_LEFT, SDL_KMOD_CTRL, []()
                                { std::cout << "Ctrl+Left Click pressed!\n"; });

    // Регистрация обработчиков мыши
    input.register_motion_callback([](int x, int y)
                                   { fmt::print("Mouse moved to: ({}, {})\n", x, y); });

    input.register_wheel_callback([](float x, float y)
                                  { fmt::print("Mouse wheel: X={:.2f}, Y={:.2f}\n", x, y); });

    input.register_click_callback(SDL_BUTTON_RIGHT, []()
                                  { std::cout << "Right button clicked!\n"; });

    // Главный цикл
    bool running = true;

    input.register_hotkey(SDLK_ESCAPE, SDL_KMOD_NONE, [&running]()
                          {   
                                std::cout << "ESC pressed! Close...\n";
                                running = false; });
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            input.handle_event(&event);
        }

        input.update();
        SDL_Delay(16);
    }

    // Освобождение ресурсов
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("Application terminated\n");

    return 0;
}