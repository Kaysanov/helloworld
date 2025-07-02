#include "HotkeyManager.h"

#include <fmt/core.h>
#include <iostream>

#include <SDL3/SDL_version.h>

int main()
{
#ifdef NDEBUG
    printf("Release configuration!\n");
#else
    printf("Debug configuration!\n");
#endif
    printf("Начало!\n");

    // Вывод версии SDL с использованием правильных макросов
    const int compiled = SDL_VERSION;  /* hardcoded number from SDL headers */
    const int linked = SDL_GetVersion();  /* reported by linked SDL library */
    
    fmt::print("SDL version: {}.{}.{}\n", 
                SDL_VERSIONNUM_MAJOR(compiled),
                SDL_VERSIONNUM_MINOR(compiled),
                SDL_VERSIONNUM_MICRO(compiled));
    

    SDL_Log("We compiled against SDL version %d.%d.%d ...\n",
        SDL_VERSIONNUM_MAJOR(compiled),
        SDL_VERSIONNUM_MINOR(compiled),
        SDL_VERSIONNUM_MICRO(compiled));

    fmt::print("{}", "Init\n");
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    fmt::print("{}", "Init END\n");

    

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Hotkey Example",
                                          800, 600, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        fmt::print("Window creation error: {}\n", SDL_GetError());
        return 1;
    }

    HotkeyManager hotkeys;

    // Регистрация комбинаций
    hotkeys.register_hotkey(SDLK_S, SDL_KMOD_CTRL, []()
                            { std::cout << "Ctrl+S pressed! Saving...\n"; });

    hotkeys.register_hotkey(SDLK_C, SDL_KMOD_CTRL, []()
                            { std::cout << "Ctrl+C pressed! Copying...\n"; });

    hotkeys.register_combo({SDLK_1, SDLK_2, SDLK_3}, []()
                           { std::cout << "Combo 1-2-3 activated!\n"; });

    hotkeys.register_hotkey(SDLK_F1, SDL_KMOD_NONE, []()
                            { std::cout << "F1 pressed! ...\n"; });

    // Главный цикл
    bool running = true;

    hotkeys.register_hotkey(SDLK_ESCAPE, SDL_KMOD_NONE, [&running]()
                            { 
                                std::cout << "Esc pressed! ...\n"; 
                                running = false;
                            });
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            hotkeys.handle_event(&event);
        }

        hotkeys.update();
      

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Конец!\n");

    return 0;
}