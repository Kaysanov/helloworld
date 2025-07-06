#include "InputProcessor.h"
#include "SDLEventGenerator.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <fmt/core.h>
#include <stdexcept> // Для исключений
#include <math.h>

#include "ConfigManager.h"

// Класс-обертка для управления ресурсами SDL
class SDLManager
{
public:
    SDLManager(const char *title, int width, int height, Uint32 flags)
    {
        // Инициализация SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw std::runtime_error(fmt::format("SDL_Init Error: {}", SDL_GetError()));
        }

        // Создание окна
        window_ = SDL_CreateWindow(title, width, height, flags);
        if (!window_)
        {
            SDL_Quit();
            throw std::runtime_error(fmt::format("SDL_CreateWindow Error: {}", SDL_GetError()));
        }

        fmt::print("SDL initialized successfully\n");
    }

    ~SDLManager()
    {
        if (window_)
        {
            SDL_DestroyWindow(window_);
            fmt::print("Window destroyed\n");
        }
        SDL_Quit();
        fmt::print("SDL shut down\n");
    }

    // Запрещаем копирование
    SDLManager(const SDLManager &) = delete;
    SDLManager &operator=(const SDLManager &) = delete;

    // Доступ к окну
    SDL_Window *window() const { return window_; }

private:
    SDL_Window *window_ = nullptr;
};

int main(int argc, char *argv[])
{
    try
    {
        SDLManager sdlManager("Input System Demo (SDL3)",
                              800, 600,
                              SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);

        // Создание системы ввода
        InputProcessor processor;
        SDLEventGenerator eventGenerator;

        // Регистрация обработчиков
        // processor.registerKeyboardHotkey(Key::S, Modifier::Ctrl,
        //                                  []
        //                                  { fmt::print("Ctrl+S: Save triggered\n"); });
        // // Регистрация обработчиков
        // processor.registerKeyboardHotkey(Key::S, Modifier::Ctrl | Modifier::Shift,
        //                                  []
        //                                  { fmt::print("Ctrl+Shift+S: Save triggered\n"); });

        // processor.registerMouseHotkey(MouseButton::Left, Modifier::Alt,
        //                               []
        //                               { fmt::print("Alt+Click action\n"); });

        /*    // Оптимизация: кэширование позиции мыши для редкого вывода
            int lastX = -1, lastY = -1;
            processor.registerMouseMoveCallback(
                [&](int x, int y)
                {
                    static int counter = 0;
                    if (++counter % 10 == 0 || (abs(x - lastX) > 50 || abs(y - lastY) > 50))
                    {
                        fmt::print("Mouse position: {}, {}\n", x, y);
                        lastX = x;
                        lastY = y;
                    }
                });

            processor.registerMouseWheelCallback(
                [](float dx, float dy)
                {
                    // Фильтрация микро-движений
                    if (fabs(dx) > 0.01f || fabs(dy) > 0.01f)
                    {
                        fmt::print("Mouse wheel: {:.2f}, {:.2f}\n", dx, dy);
                    }
                });
        */

        // Обработка события выхода
        /*processor.registerKeyboardHotkey(Key::Q, Modifier::Ctrl,
                                         [&]
                                         {
                                             SDL_Event evt{};
                                             evt.type = SDL_EVENT_QUIT;
                                             SDL_PushEvent(&evt);
                                         });*/

        // Определение действий
        ConfigManager::ActionMap actions = {
            {"save", []
                    {   fmt::print("Save triggered\n"); }},
            {"exit", [&]
                {
                    SDL_Event evt{};
                    evt.type = SDL_EVENT_QUIT;
                    SDL_PushEvent(&evt);
                }},
            {"custom_action", []
                {   fmt::print("Custom action\n"); }}};
        // Загрузка конфигурации
        ConfigManager::loadConfig("config.json", processor, actions);

        // Запуск основного цикла
        eventGenerator.runEventLoop(processor);

        fmt::print("Exiting...\n");

        return 0;
    }
    catch (const std::exception &e)
    {
        fmt::print(stderr, "Error: {}\n", e.what());
        return 1;
    }
}