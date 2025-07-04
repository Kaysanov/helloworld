#include "SDLInputSystem.h"
#include "HotkeyManager.h"
#include "ConfigManager.h"
#include <iostream>
#include <memory>

int main()
{
    // Инициализация системы ввода
    std::unique_ptr<InputSystem> inputSystem = std::make_unique<SDLInputSystem>();
    if (!inputSystem->initialize())
    {
        std::cerr << "Input system initialization failed\n";
        return 1;
    }

    // Создание окна
    void *window = inputSystem->createWindow("Input Manager Demo", 800, 600);
    if (!window)
    {
        std::cerr << "Window creation failed\n";
        inputSystem->shutdown();
        return 1;
    }

    HotkeyManager manager;
    bool running = true;

    // Регистрация обработчиков мыши
    /*manager.registerMouseMoveCallback([](int x, int y) {
            std::cout << "Mouse position: " << x << ", " << y << "\n";
    });*/
    // Регистрация обработчиков мыши
    manager.registerMouseWheelCallback([](float x, float y)
                                       { std::cout << "Mouse Wheel position: " << x << ", " << y << "\n"; });

    manager.registerClickCallback(MouseButton::Right, []
                                  { std::cout << "Right mouse button clicked\n"; });

    // Регистрация горячих клавиш через шаблонную функцию
    manager.registerHotkey(Key::S, Modifier::LeftCtrl, []
                           { std::cout << "LeftCtrl+S pressed\n"; });

    manager.registerHotkey(Key::S, Modifier::LeftShift, []
                           { std::cout << "LeftShift+S pressed\n"; });
                    
    manager.registerHotkey(Key::S, Modifier::LeftCtrl | Modifier::LeftShift, []
                           { std::cout << "LeftCtrl+LeftShift+S pressed\n"; });

    // Регистрация Ctrl+Q для выхода
    manager.registerHotkey(Key::Escape, Modifier::None, [&running]
                           {
        std::cout << "Escape pressed - quitting" << std::endl;
        running = false; });

    manager.registerHotkey(MouseButton::Left, Modifier::LeftCtrl | Modifier::LeftAlt, []
                           { std::cout << "Right Ctrl+Left Alt+Left Mouse pressed\n"; });

    std::cout << "Application started. Press:\n";
    std::cout << "  Left Ctrl+S - Test left Ctrl\n";
    std::cout << "  Right Ctrl+S - Test right Ctrl\n";
    std::cout << "  Escape - Quit\n";
    std::cout << "  Right mouse button - Test click\n";
    std::cout << "  Right Ctrl+Left Alt+Left Mouse - Special combo\n\n";

    // Главный цикл
    while (running)
    {
        inputSystem->pollEvents();
        manager.processEvents(inputSystem->getEvents());
        manager.update();

        // Здесь может быть рендеринг
        SDL_Delay(16);
    }

    inputSystem->destroyWindow(window);
    inputSystem->shutdown();
    std::cout << "Application terminated\n";
    return 0;
}