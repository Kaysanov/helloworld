// Загрузка конфигурации из файла
#include "ConfigManager.h"
#include <fmt/core.h>
#include <algorithm>

// Преобразование Key в строку
std::string ConfigManager::keyToString(Key key) 
{
    switch (key)
    {
    case Key::A:
        return "A";
    case Key::B:
        return "B";
    case Key::C:
        return "C";
    case Key::D:
        return "D";
    case Key::E:
        return "E";
    case Key::F:
        return "F";
    case Key::G:
        return "G";
    case Key::H:
        return "H";
    case Key::I:
        return "I";
    case Key::J:
        return "J";
    case Key::K:
        return "K";
    case Key::L:
        return "L";
    case Key::M:
        return "M";
    case Key::N:
        return "N";
    case Key::O:
        return "O";
    case Key::P:
        return "P";
    case Key::Q:
        return "Q";
    case Key::R:
        return "R";
    case Key::S:
        return "S";
    case Key::T:
        return "T";
    case Key::U:
        return "U";
    case Key::V:
        return "V";
    case Key::W:
        return "W";
    case Key::X:
        return "X";
    case Key::Y:
        return "Y";
    case Key::Z:
        return "Z";
    case Key::Num0:
        return "0";
    case Key::Num1:
        return "1";
    case Key::Num2:
        return "2";
    case Key::Num3:
        return "3";
    case Key::Num4:
        return "4";
    case Key::Num5:
        return "5";
    case Key::Num6:
        return "6";
    case Key::Num7:
        return "7";
    case Key::Num8:
        return "8";
    case Key::Num9:
        return "9";
    case Key::Escape:
        return "Escape";
    case Key::Enter:
        return "Enter";
    case Key::Space:
        return "Space";
    case Key::Tab:
        return "Tab";
    case Key::Backspace:
        return "Backspace";
    case Key::Delete:
        return "Delete";
    case Key::LeftCtrl:
        return "LeftCtrl";
    case Key::RightCtrl:
        return "RightCtrl";
    case Key::LeftShift:
        return "LeftShift";
    case Key::RightShift:
        return "RightShift";
    case Key::LeftAlt:
        return "LeftAlt";
    case Key::RightAlt:
        return "RightAlt";
    case Key::LeftSuper:
        return "LeftSuper";
    case Key::RightSuper:
        return "RightSuper";
    case Key::F1:
        return "F1";
    case Key::F2:
        return "F2";
    case Key::F3:
        return "F3";
    case Key::F4:
        return "F4";
    case Key::F5:
        return "F5";
    case Key::F6:
        return "F6";
    case Key::F7:
        return "F7";
    case Key::F8:
        return "F8";
    case Key::F9:
        return "F9";
    case Key::F10:
        return "F10";
    case Key::F11:
        return "F11";
    case Key::F12:
        return "F12";
    case Key::Left:
        return "Left";
    case Key::Right:
        return "Right";
    case Key::Up:
        return "Up";
    case Key::Down:
        return "Down";
    default:
        return "Unknown";
    }
}

// Преобразование строки в Key
Key ConfigManager::stringToKey(const std::string &str)
{
    static const std::unordered_map<std::string, Key> keyMap = {
        {"A", Key::A}, {"B", Key::B}, {"C", Key::C}, {"D", Key::D}, {"E", Key::E}, {"F", Key::F}, {"G", Key::G}, {"H", Key::H}, {"I", Key::I}, {"J", Key::J}, {"K", Key::K}, {"L", Key::L}, {"M", Key::M}, {"N", Key::N}, {"O", Key::O}, {"P", Key::P}, {"Q", Key::Q}, {"R", Key::R}, {"S", Key::S}, {"T", Key::T}, {"U", Key::U}, {"V", Key::V}, {"W", Key::W}, {"X", Key::X}, {"Y", Key::Y}, {"Z", Key::Z}, {"0", Key::Num0}, {"1", Key::Num1}, {"2", Key::Num2}, {"3", Key::Num3}, {"4", Key::Num4}, {"5", Key::Num5}, {"6", Key::Num6}, {"7", Key::Num7}, {"8", Key::Num8}, {"9", Key::Num9}, {"Escape", Key::Escape}, {"Enter", Key::Enter}, {"Space", Key::Space}, {"Tab", Key::Tab}, {"Backspace", Key::Backspace}, {"Delete", Key::Delete}, {"LeftCtrl", Key::LeftCtrl}, {"RightCtrl", Key::RightCtrl}, {"LeftShift", Key::LeftShift}, {"RightShift", Key::RightShift}, {"LeftAlt", Key::LeftAlt}, {"RightAlt", Key::RightAlt}, {"LeftSuper", Key::LeftSuper}, {"RightSuper", Key::RightSuper}, {"F1", Key::F1}, {"F2", Key::F2}, {"F3", Key::F3}, {"F4", Key::F4}, {"F5", Key::F5}, {"F6", Key::F6}, {"F7", Key::F7}, {"F8", Key::F8}, {"F9", Key::F9}, {"F10", Key::F10}, {"F11", Key::F11}, {"F12", Key::F12}, {"Left", Key::Left}, {"Right", Key::Right}, {"Up", Key::Up}, {"Down", Key::Down}};

    auto it = keyMap.find(str);
    if (it != keyMap.end())
    {
        return it->second;
    }
    throw std::runtime_error("Unknown key: " + str);
}

// Преобразование MouseButton в строку
std::string ConfigManager::buttonToString(MouseButton button)
{
    switch (button)
    {
    case MouseButton::Left:
        return "Left";
    case MouseButton::Right:
        return "Right";
    case MouseButton::Middle:
        return "Middle";
    case MouseButton::Extra1:
        return "Extra1";
    case MouseButton::Extra2:
        return "Extra2";
    default:
        return "Unknown";
    }
}

// Преобразование строки в MouseButton
MouseButton ConfigManager::stringToButton(const std::string &str)
{
    if (str == "Left")
        return MouseButton::Left;
    if (str == "Right")
        return MouseButton::Right;
    if (str == "Middle")
        return MouseButton::Middle;
    if (str == "Extra1")
        return MouseButton::Extra1;
    if (str == "Extra2")
        return MouseButton::Extra2;
    throw std::runtime_error("Unknown mouse button: " + str);
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
                std::string action_id = item["action"].get<std::string>();
                Key key = stringToKey(item["key"].get<std::string>());
                uint16_t mods = stringsToModifiers(item["modifiers"].get<std::vector<std::string>>());
                fmt::print("Registering keyboard hotkey: {}\n", action_id);
                fmt::print("Key: {}\n", item["key"].get<std::string>());
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
                    if (event_type == "release")
                    {
                        processor.registerKeyRelease(key, mods, actions.at(action_id));
                    }
                    else
                    {
                        processor.registerKeyboardHotkey(key, mods, actions.at(action_id));
                    }
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
                std::string action_id = item["action"].get<std::string>();
                MouseButton button = stringToButton(item["button"].get<std::string>());
                uint16_t mods = stringsToModifiers(item["modifiers"].get<std::vector<std::string>>());

                std::string event_type = "press";
                if (item.contains("event"))
                {
                    event_type = item["event"].get<std::string>();
                }

                // Регистрация горячей клавиши мыши
                if (actions.find(action_id) != actions.end())
                {
                    if (event_type == "release")
                    {
                        processor.registerMouseButtonRelease(button, mods, actions.at(action_id));
                    }
                    else
                    {
                        processor.registerMouseHotkey(button, mods, actions.at(action_id));
                    }
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