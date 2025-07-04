#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "HotkeyManager.h"
#include <nlohmann/json.hpp>
#include <string>
#include <functional>
#include <unordered_map>

using json = nlohmann::json;

class ConfigManager
{
public:
    using ActionMap = std::unordered_map<std::string, std::function<void()>>;

    // Загрузка конфигурации
    static bool load_config(const std::string &filename,
                            HotkeyManager &hm,
                            const ActionMap &actions);

    // Сохранение конфигурации
    static bool save_config(const std::string &filename,
                            const HotkeyManager &hm);

private:
    // Вспомогательные функции преобразования
    static std::string keycode_to_string(SDL_Keycode key);
    static SDL_Keycode string_to_keycode(const std::string &str);
    static std::string button_to_string(Uint8 button);
    static Uint8 string_to_button(const std::string &str);
    static std::vector<std::string> modifiers_to_strings(SDL_Keymod mods);
    static SDL_Keymod strings_to_modifiers(const std::vector<std::string> &mods);
};

#endif // CONFIGMANAGER_H