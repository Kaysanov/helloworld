// Загрузка конфигурации из файла
#include "ConfigManager.h"
#include <fmt/core.h>
#include <algorithm>

// Преобразование Key в строку
std::string ConfigManager::keyToString(Key key) 
{
    return KeytoString(key);
}

// Преобразование строки в Key
Key ConfigManager::stringToKey(const std::string &str)
{
   return KeyfromString(str);
}

// Преобразование MouseButton в строку
std::string ConfigManager::buttonToString(MouseButton button)
{
    return MouseButtontoString(button);
}

// Преобразование строки в MouseButton
MouseButton ConfigManager::stringToButton(const std::string &str)
{
   return MouseButtonfromString(str);
}

// Преобразование модификаторов в строки
std::vector<std::string> ConfigManager::modifiersToStrings(uint16_t modifiers)
{
    std::vector<std::string> result;

    if (modifiers & Modifier::LeftCtrl)
        result.push_back("LeftCtrl");
    if (modifiers & Modifier::RightCtrl)
        result.push_back("RightCtrl");
    if (modifiers & Modifier::LeftShift)
        result.push_back("LeftShift");
    if (modifiers & Modifier::RightShift)
        result.push_back("RightShift");
    if (modifiers & Modifier::LeftAlt)
        result.push_back("LeftAlt");
    if (modifiers & Modifier::RightAlt)
        result.push_back("RightAlt");
    if (modifiers & Modifier::LeftSuper)
        result.push_back("LeftSuper");
    if (modifiers & Modifier::RightSuper)
        result.push_back("RightSuper");

    return result;
}

// Преобразование строк в модификаторы
uint16_t ConfigManager::stringsToModifiers(const std::vector<std::string> &mods)
{
    uint16_t result = Modifier::None;

    for (const auto &m : mods)
    {
        fmt::print(stderr, "Modifier: {}\n", m);
        if (m == "LeftCtrl")
            result |= Modifier::Ctrl;
        else if (m == "RightCtrl")
            result |= Modifier::Ctrl;
        else if (m == "LeftShift")
            result |= Modifier::LeftShift;
        else if (m == "RightShift")
            result |= Modifier::RightShift;
        else if (m == "LeftAlt")
            result |= Modifier::LeftAlt;
        else if (m == "RightAlt")
            result |= Modifier::RightAlt;
        else if (m == "LeftSuper")
            result |= Modifier::LeftSuper;
        else if (m == "RightSuper")
            result |= Modifier::RightSuper;
    }
    fmt::print(stderr, "Modifier result: {}\n", result);
    return result;
}

// Загрузка конфигурации из файла
void ConfigManager::loadConfig(
    const std::string &filename,
    InputProcessor &processor,
    const ActionMap &actions)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error(fmt::format("Failed to open config file: {}", filename));
    }

    json config;
    file >> config;
    file.close();

    // Загрузка клавиатурных комбинаций
    if (config.contains("keyboard_hotkeys") && config["keyboard_hotkeys"].is_array())
    {
        for (const auto &item : config["keyboard_hotkeys"])
        {
            try
            {
                // ... получение параметров ...
                std::string state = item["state"].get<std::string>();
                std::string action_id = item["action"].get<std::string>();
                std::string key = item["key"].get<std::string>();

                uint16_t mods = stringsToModifiers(item["modifiers"].get<std::vector<std::string>>());
                
                fmt::print("Registering keyboard hotkey: {}, {}\n", action_id, key);
                
                // fmt::print("Modifiers: {}\n", item["modifiers"].get<std::vector<std::string>>());

                // Определение типа события
                std::string event_type = "press"; // значение по умолчанию
                if (item.contains("event"))
                {
                    event_type = item["event"].get<std::string>();
                }

                // Регистрация горячей клавиши
                if (actions.find(action_id) != actions.end())
                {
                    processor.getHotkeyHandler()->registerAction(state, key, mods,
                                                                     actions.at(action_id), event_type == "release");                    
                }
                else
                {
                    fmt::print(stderr, "Action not registered: {}\n", action_id);
                }
            }
            catch (const std::exception &e)
            {
                fmt::print(stderr, "Error parsing keyboard hotkey: {}\n", e.what());
            }
        }
    }

    // Загрузка мышиных комбинаций
    if (config.contains("mouse_hotkeys") && config["mouse_hotkeys"].is_array())
    {
        for (const auto &item : config["mouse_hotkeys"])
        {
            try
            {
                std::string state = item["state"].get<std::string>();
                std::string action_id = item["action"].get<std::string>();                
                std::string button = item["key"].get<std::string>();
                uint16_t mods = stringsToModifiers(item["modifiers"].get<std::vector<std::string>>());

                std::string event_type = "press";
                if (item.contains("event"))
                {
                    event_type = item["event"].get<std::string>();
                }

                // Регистрация горячей клавиши мыши
                if (actions.find(action_id) != actions.end())
                {
                   processor.getHotkeyHandler()->registerAction(state, button, mods,
                                                                     actions.at(action_id), event_type == "release");                    
                }
                else
                {
                    fmt::print(stderr, "Action not registered: {}\n", action_id);
                }
            }
            catch (const std::exception &e)
            {
                fmt::print(stderr, "Error parsing mouse hotkey: {}\n", e.what());
            }
        }
    }
}

// Сохранение конфигурации в файл
void ConfigManager::saveConfig(
    const std::string &filename,
    InputProcessor &processor,
    const std::vector<std::pair<std::string, Key>> &keyboardActions,
    const std::vector<std::pair<std::string, MouseButton>> &mouseActions)
{
    json config;

    // Сохранение клавиатурных комбинаций
    json keyboardArray = json::array();
    for (const auto &[action_id, key] : keyboardActions)
    {
        json item;
        item["action"] = action_id;
        item["key"] = keyToString(key);

        // Получаем текущие модификаторы для этого действия
        // (В реальной реализации нужно хранить модификаторы для каждого действия)
        item["modifiers"] = modifiersToStrings(Modifier::Ctrl); // Пример
        keyboardArray.push_back(item);
    }
    config["keyboard_hotkeys"] = keyboardArray;

    // Сохранение мышиных комбинаций
    json mouseArray = json::array();
    for (const auto &[action_id, button] : mouseActions)
    {
        json item;
        item["action"] = action_id;
        item["button"] = buttonToString(button);

        // Получаем текущие модификаторы для этого действия
        item["modifiers"] = modifiersToStrings(Modifier::Alt); // Пример
        mouseArray.push_back(item);
    }
    config["mouse_hotkeys"] = mouseArray;

    // Запись в файл
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error(fmt::format("Failed to open file for writing: {}", filename));
    }

    file << config.dump(4); // Красивый вывод с отступами
    file.close();
}