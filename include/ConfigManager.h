#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "InputProcessor.h"
#include <string>
#include <vector>

class ConfigManager
{
public:
    // Загрузка конфигурации
    static void loadConfig(
        const std::string &filename,
        InputProcessor &processor);

    // Сохранение конфигурации
    static void saveConfig(
        const std::string &filename,
        const InputProcessor &processor);

private:
    static std::vector<std::string> modifiersToStrings(uint16_t modifiers);
    static uint16_t stringsToModifiers(const std::vector<std::string> &mods);
};

#endif // CONFIGMANAGER_H