#include "SDLManager.h"
#include "SDL3EventGenerator.h"
#include "InputProcessor.h"
#include "ConfigManager.h"
#include <fmt/core.h>

const std::string CONFIG_FILE = "config.json";

int main(int argc, char *argv[])
{
    try
    {
        // 1. Инициализация базовых систем (например, SDL)
        SDLManager sdlManager("Input System Demo", 800, 600, SDL_WINDOW_RESIZABLE);

        // 2. Создание центрального обработчика ввода
        InputProcessor processor;

        // 3. ОПРЕДЕЛЕНИЕ ДЕЙСТВИЙ (Что делать?)
        // Определяем все возможные действия в приложении и их логику.
        // Имена действий ("Jump", "Fire", "Quit") - это ключи, которые будут
        // использоваться в файле конфигурации.
        processor.defineActions({{"Jump", []()
                                  { fmt::print("Action: Jump!\n"); }},
                                 {"Crouch", []()
                                  { fmt::print("Action: Crouch!\n"); }},
                                 {"Fire", []()
                                  { fmt::print("Action: Fire!\n"); }},
                                 {"ToggleMenu", [&]()
                                  {
                                      // Пример переключения состояний
                                      if (processor.getCurrentState() == "Default")
                                      {
                                          processor.setState("Menu");
                                          fmt::print("State changed to Menu\n");
                                      }
                                      else
                                      {
                                          processor.setState("Default");
                                          fmt::print("State changed to Default\n");
                                      }
                                  }},
                                 {"Quit", []()
                                  {
                                      // Чтобы выйти из цикла SDL, мы отправляем стандартное событие выхода.
                                      fmt::print("Action: Quit! Pushing SDL_EVENT_QUIT.\n");
                                      SDL_Event quit_event;
                                      quit_event.type = SDL_EVENT_QUIT;
                                      SDL_PushEvent(&quit_event);
                                  }}});

        // 4. НАЗНАЧЕНИЕ ПРИВЯЗОК ПО УМОЛЧАНИЮ (Как вызывать?)
        // Эти привязки будут использоваться, если файл конфигурации отсутствует.
        fmt::print("Registering default bindings...\n");

        // Привязки для состояния "Default"
        processor.registerKeyBinding("Default", "Jump", "Space", Modifier::None);
        processor.registerKeyBinding("Default", "Crouch", "C", Modifier::None);
        processor.registerMouseButtonBinding("Default", "Fire", "Left", Modifier::None);

        // Привязки, общие для всех состояний
        processor.registerKeyBinding("Default", "ToggleMenu", "Tab", Modifier::None);
        processor.registerKeyBinding("Menu", "ToggleMenu", "Tab", Modifier::None);
        processor.registerKeyBinding("Default", "Quit", "Escape", Modifier::None);
        processor.registerKeyBinding("Menu", "Quit", "Escape", Modifier::None);

        // Привязка колбэков для непрерывного ввода (движение мыши)
        processor.registerMouseMoveCallback("Default", [](int x, int y)
                                            {
            // Чтобы избежать спама в консоль, будем выводить сообщение нечасто
            static int count = 0;
            if (++count % 10 == 0) fmt::print("Callback: Mouse moved to ({}, {})\n", x, y); });

        // 5. ЗАГРУЗКА ПОЛЬЗОВАТЕЛЬСКОЙ КОНФИГУРАЦИИ
        // ConfigManager переопределит привязки по умолчанию теми, что найдет в файле.
        ConfigManager::loadConfig(CONFIG_FILE, processor);

        // 6. Запуск основного цикла приложения
        SDL3EventGenerator eventGenerator;
        fmt::print("\n--- Starting Event Loop ---\n");
        fmt::print("Try pressing Space, C, Left Mouse Button, Tab, or Escape. Try moving the mouse.\n");
        eventGenerator.runEventLoop(processor); // Блокирующий вызов
        fmt::print("--- Event Loop Finished ---\n\n");

        // 7. Сохранение конфигурации перед выходом
        // Это сохранит текущие привязки (полезно, если в будущем появится
        // меню для их изменения во время выполнения).
        ConfigManager::saveConfig(CONFIG_FILE, processor);
    }
    catch (const std::exception &e)
    {
        fmt::print(stderr, "An error occurred: {}\n", e.what());
        return 1;
    }

    return 0;
}
