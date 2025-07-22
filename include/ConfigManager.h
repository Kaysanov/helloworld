#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <vector>

class InputProcessor; // Forward declaration

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
};

#endif // CONFIGMANAGER_H