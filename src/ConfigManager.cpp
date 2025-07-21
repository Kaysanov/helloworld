#include "ConfigManager.h"
#include "InputProcessor.h"
#include "key.h"
#include "mousebutton.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <fmt/core.h>

using json = nlohmann::json;

// --- Вспомогательные функции ---

std::vector<std::string> ConfigManager::modifiersToStrings(uint16_t modifiers)
{
    std::vector<std::string> mods;
    if (modifiers & Modifier::Ctrl)
        mods.push_back("Ctrl");
    if (modifiers & Modifier::Shift)
        mods.push_back("Shift");
    if (modifiers & Modifier::Alt)
        mods.push_back("Alt");
    if (modifiers & Modifier::Super)
        mods.push_back("Super");
    return mods;
}

uint16_t ConfigManager::stringsToModifiers(const std::vector<std::string> &mods)
{
    uint16_t result = Modifier::None;
    for (const auto &mod_str : mods)
    {
        if (mod_str == "Ctrl")
            result |= Modifier::Ctrl;
        else if (mod_str == "Shift")
            result |= Modifier::Shift;
        else if (mod_str == "Alt")
            result |= Modifier::Alt;
        else if (mod_str == "Super")
            result |= Modifier::Super;
    }
    return result;
}

// --- Публичное API ---

void ConfigManager::saveConfig(const std::string &filename, const InputProcessor &processor)
{
    json config_json;
    json kb_bindings;
    json mouse_bindings;

    // Для простоты сохраняем привязки только для состояния "Default".
    const std::string state = "Default";

    auto &hotkeyHandler = processor.getHotkeyHandler();
    auto &mouseHandler = processor.getMouseHandler();

    for (const auto &actionName : processor.getActionNames())
    {
        // Сохраняем привязку клавиатуры, если она есть
        if (auto binding = hotkeyHandler.findBindingForAction(actionName, state))
        {
            json b;
            b["key"] = KeytoString(binding->key);
            b["modifiers"] = modifiersToStrings(binding->modifiers);
            kb_bindings[actionName] = b;
        }

        // Сохраняем привязку мыши, если она есть (независимо от клавиатуры)
        if (auto binding = mouseHandler.findBindingForAction(actionName, state))
        {
            json b;
            b["button"] = MouseButtonToString(binding->button);
            b["modifiers"] = modifiersToStrings(binding->modifiers);
            mouse_bindings[actionName] = b;
        }
    }

    config_json["keyboard_bindings"] = kb_bindings;
    config_json["mouse_bindings"] = mouse_bindings;

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

    const std::string state = "Default"; // Загружаем в состояние "Default"

    auto load_bindings = [&](const json &bindings, const std::string &type)
    {
        if (!bindings.is_object())
            return;
        for (const auto &[actionName, info] : bindings.items())
        {
            try
            {
                uint16_t modifiers = info.contains("modifiers")
                                         ? stringsToModifiers(info["modifiers"].get<std::vector<std::string>>())
                                         : Modifier::None;
                if (type == "keyboard" && info.contains("key"))
                {
                    processor.getHotkeyHandler().registerBinding(state, actionName, info["key"].get<std::string>(), modifiers);
                }
                else if (type == "mouse" && info.contains("button"))
                {
                    processor.getMouseHandler().registerBinding(state, actionName, info["button"].get<std::string>(), modifiers);
                }
            }
            catch (const std::exception &e)
            {
                fmt::print(stderr, "Error processing binding for action '{}': {}\n", actionName, e.what());
            }
        }
    };

    if (config_json.contains("keyboard_bindings"))
    {
        load_bindings(config_json["keyboard_bindings"], "keyboard");
    }
    if (config_json.contains("mouse_bindings"))
    {
        load_bindings(config_json["mouse_bindings"], "mouse");
    }

    fmt::print("Configuration loaded from {}.\n", filename);
}