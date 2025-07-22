#include "ConfigManager.h"
#include "InputProcessor.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <fmt/core.h>

using json = nlohmann::json;

void ConfigManager::saveConfig(const std::string &filename, const InputProcessor &processor)
{
    json config_json = processor.exportConfiguration();

    try
    {
        std::ofstream file(filename);
        file << config_json.dump(4);
        fmt::print("Configuration saved to {}.\n", filename);
    }
    catch (const std::exception &e)
    {
        fmt::print(stderr, "Error saving configuration to {}: {}\n", filename, e.what());
    }
}

void ConfigManager::loadConfig(const std::string &filename, InputProcessor &processor)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        fmt::print("Configuration file {} not found. Using default bindings.\n", filename);
        return;
    }

    json config_json;
    try
    {
        file >> config_json;
    }
    catch (const json::parse_error &e)
    {
        fmt::print(stderr, "Error parsing configuration file {}: {}\n", filename, e.what());
        return;
    }

    processor.importConfiguration(config_json);
    fmt::print("Configuration loaded from {}.\n", filename);
}