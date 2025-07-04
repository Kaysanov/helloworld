#include "ConfigManager.h"
#include <fstream>
#include <stdexcept>
#include <SDL3/SDL.h>
#include <fmt/core.h>

// Преобразование SDL_Keycode в строку
std::string ConfigManager::keycode_to_string(SDL_Keycode key)
{
    const char *name = SDL_GetKeyName(key);
    return name ? std::string(name) : "Unknown";
}

// Преобразование строки в SDL_Keycode
SDL_Keycode ConfigManager::string_to_keycode(const std::string &str)
{
    SDL_Keycode key = SDL_GetKeyFromName(str.c_str());
    if (key == SDLK_UNKNOWN)
    {
        throw std::runtime_error("Unknown key: " + str);
    }
    return key;
}

// Преобразование кнопки мыши в строку
std::string ConfigManager::button_to_string(Uint8 button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return "Left";
    case SDL_BUTTON_RIGHT:
        return "Right";
    case SDL_BUTTON_MIDDLE:
        return "Middle";
    case SDL_BUTTON_X1:
        return "X1";
    case SDL_BUTTON_X2:
        return "X2";
    default:
        return "Unknown";
    }
}

// Преобразование строки в кнопку мыши
Uint8 ConfigManager::string_to_button(const std::string &str)
{
    if (str == "Left")
        return SDL_BUTTON_LEFT;
    if (str == "Right")
        return SDL_BUTTON_RIGHT;
    if (str == "Middle")
        return SDL_BUTTON_MIDDLE;
    if (str == "X1")
        return SDL_BUTTON_X1;
    if (str == "X2")
        return SDL_BUTTON_X2;
    throw std::runtime_error("Unknown mouse button: " + str);
}

// Преобразование модификаторов в строки
std::vector<std::string> ConfigManager::modifiers_to_strings(SDL_Keymod mods)
{
    std::vector<std::string> result;
    if (mods & SDL_KMOD_CTRL)
        result.push_back("Ctrl");
    if (mods & SDL_KMOD_SHIFT)
        result.push_back("Shift");
    if (mods & SDL_KMOD_ALT)
        result.push_back("Alt");
    if (mods & SDL_KMOD_GUI)
        result.push_back("GUI");
    return result;
}

// Преобразование строк в модификаторы
SDL_Keymod ConfigManager::strings_to_modifiers(const std::vector<std::string> &mods)
{
    SDL_Keymod result = SDL_KMOD_NONE;
    for (const auto &m : mods)
    {
        if (m == "Ctrl")
            result = static_cast<SDL_Keymod>(result | SDL_KMOD_CTRL);
        else if (m == "Shift")
            result = static_cast<SDL_Keymod>(result | SDL_KMOD_SHIFT);
        else if (m == "Alt")
            result = static_cast<SDL_Keymod>(result | SDL_KMOD_ALT);
        else if (m == "GUI")
            result = static_cast<SDL_Keymod>(result | SDL_KMOD_GUI);
    }
    return result;
}

// Загрузка конфигурации из JSON
bool ConfigManager::load_config(const std::string &filename,
                                HotkeyManager &hm,
                                const ActionMap &actions)
{
    try
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            fmt::print("Failed to open file: {}\n", filename);
            return false;
        }

        json config = json::parse(file);

        // Загрузка клавиатурных комбинаций
        if (config.contains("keyboard_hotkeys"))
        {
            for (const auto &item : config["keyboard_hotkeys"])
            {
                std::string action_id = item["action"];
                SDL_Keycode key = string_to_keycode(item["key"]);
                SDL_Keymod mods = strings_to_modifiers(item["modifiers"]);

                if (actions.find(action_id) != actions.end())
                {
                    hm.register_hotkey(key, mods, actions.at(action_id));
                }
            }
        }

        // Загрузка мышиных комбинаций
        if (config.contains("mouse_hotkeys"))
        {
            for (const auto &item : config["mouse_hotkeys"])
            {
                std::string action_id = item["action"];
                Uint8 button = string_to_button(item["button"]);
                SDL_Keymod mods = strings_to_modifiers(item["modifiers"]);

                if (actions.find(action_id) != actions.end())
                {
                    hm.register_mouse_hotkey(button, mods, actions.at(action_id));
                }
            }
        }

        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
}

// Сохранение конфигурации в JSON
bool ConfigManager::save_config(const std::string &filename,
                                const HotkeyManager &hm)
{
    // В реальной реализации здесь будет код для получения
    // текущих горячих клавиш из HotkeyManager
    // (для этого нужно добавить соответствующие методы в HotkeyManager)
    // Покажем пример структуры

    json config;

    // Пример клавиатурных комбинаций
    config["keyboard_hotkeys"] = {
        {{"action", "save"}, {"key", "S"}, {"modifiers", {"Ctrl"}}},
        {{"action", "quit"}, {"key", "Q"}, {"modifiers", {"Ctrl", "Shift"}}}};

    // Пример мышиных комбинаций
    config["mouse_hotkeys"] = {
        {{"action", "special"}, {"button", "Left"}, {"modifiers", {"Ctrl", "Shift"}}}};

    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    file << config.dump(4); // Красивый вывод с отступами
    return true;
}