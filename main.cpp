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
        

        // Главный цикл
        SDLEventGenerator eventGenerator;
        eventGenerator.runEventLoop(processor);

        return 0;
    }
    catch (const std::exception &e)
    {
        fmt::print(stderr, "Error: {}\n", e.what());
        return 1;
    }
}