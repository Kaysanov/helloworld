#include "InputProcessor.h"
#include "SDL3EventGenerator.h"
#include <fmt/core.h>
#include <stdexcept> // Для исключений
#include <math.h>

#include "ConfigManager.h"
#include "SDLManager.h"

int main(int argc, char *argv[])
{
    try
    {
        SDLManager sdlManager("Input System Demo (SDL3)",
                              800, 600,
                              SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);
        // SDLManager sdlManager("Input System Demo (SDL3)",
        //                     800, 600,
        //                    SDL_WINDOW_RESIZABLE );

        // Создание системы ввода
        InputProcessor processor;

        processor.registerAction(
            "Default", Key::S, Modifier::LeftCtrl,
            []()
            {
                fmt::print("{}", "Ctrl+S pressed! Saving...\n");
            });
        processor.registerAction(
            "Default", Key::F1, Modifier::None,
            [&]()
            {
                fmt::print("{}", "F1 pressed! Перевод в state \"Edit\"...\n");
                processor.getStateManager().setState("Edit");
            });
        processor.registerAction(
            "Edit", Key::F1, Modifier::None,
            [&]()
            {
                fmt::print("{}", "F1 pressed! Перевод в state \"Default\"...\n");
                processor.getStateManager().setState("Default");
            });

        // Главный цикл
        SDL3EventGenerator eventGenerator;
        eventGenerator.runEventLoop(processor);

        return 0;
    }
    catch (const std::exception &e)
    {
        fmt::print(stderr, "Error: {}\n", e.what());
        return 1;
    }
}