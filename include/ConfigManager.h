#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "InputProcessor.h"
#include "InputTypes.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include <memory>

using json = nlohmann::json;

class ConfigManager
{
public:
    using ActionMap = std::unordered_map<std::string, std::function<void()>>;

    // Загрузка конфигурации
    static void loadConfig(
        const std::string &filename,
        InputProcessor &processor,
        const ActionMap &actions);

    // Сохранение конфигурации
    static void saveConfig(
        const std::string &filename,
        InputProcessor &processor,
        const std::vector<std::pair<std::string, Key>> &keyboardActions,
        const std::vector<std::pair<std::string, MouseButton>> &mouseActions);

private:
    // Вспомогательные методы преобразования
    static std::string keyToString(Key key);
    static Key stringToKey(const std::string &str);
    static std::string buttonToString(MouseButton button);
    static MouseButton stringToButton(const std::string &str);
    static std::vector<std::string> modifiersToStrings(uint16_t modifiers);
    static uint16_t stringsToModifiers(const std::vector<std::string> &mods);
};

#endif // CONFIGMANAGER_H