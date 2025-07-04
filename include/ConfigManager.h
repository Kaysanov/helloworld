#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "InputTypes.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <functional>

using json = nlohmann::json;

class ConfigManager {
public:
    using ActionMap = std::unordered_map<std::string, std::function<void()>>;
    
    // Загрузка конфигурации
    static bool loadConfig(const std::string& filename, 
                           const ActionMap& actions,
                           std::vector<std::pair<Key, uint16_t>>& keyboardHotkeys,
                           std::vector<std::pair<MouseButton, uint16_t>>& mouseHotkeys);
    
    // Сохранение конфигурации
    static bool saveConfig(const std::string& filename,
                          const std::vector<std::tuple<std::string, Key, uint16_t>>& keyboardConfigs,
                          const std::vector<std::tuple<std::string, MouseButton, uint16_t>>& mouseConfigs);

//private:
    // Преобразование типов
    static std::string keyToString(Key key);
    static Key stringToKey(const std::string& str);
    static std::string buttonToString(MouseButton button);
    static MouseButton stringToButton(const std::string& str);
    static std::vector<std::string> modifiersToStrings(uint16_t modifiers);
    static uint16_t stringsToModifiers(const std::vector<std::string>& mods);
};

#endif // CONFIGMANAGER_H