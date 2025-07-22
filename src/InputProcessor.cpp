#include "InputProcessor.h"
#include <utility>

InputProcessor::InputProcessor()
    : hotkeyHandler(*this, stateManager), mouseHandler(*this, stateManager)
{
    addHandler(&hotkeyHandler);
    addHandler(&mouseHandler);
}

void InputProcessor::handleEvent(const InputEvent &event)
{
    stateManager.updateFromEvent(event);

    for (auto handler : handlers)
    {
        handler->handleEvent(event);
    }
}


void InputProcessor::defineAction(std::string_view name, std::function<void()> callback)
{
    actionMap_[std::string(name)] = std::move(callback);
}

void InputProcessor::defineActions(const ActionMap &actions)
{
    for (const auto &pair : actions)
    {
        defineAction(pair.first, pair.second);
    }
}

void InputProcessor::triggerAction(const std::string &actionName)
{
    auto it = actionMap_.find(actionName);
    if (it != actionMap_.end() && it->second)
    {
        it->second(); // Выполняем колбэк
    }
    // Можно добавить логирование, если действие не найдено
}

std::vector<std::string> InputProcessor::getActionNames() const
{
    std::vector<std::string> names;
    names.reserve(actionMap_.size());
    for (const auto &pair : actionMap_)
    {
        names.push_back(pair.first);
    }
    return names;
}

void InputProcessor::registerKeyBinding(std::string_view state, std::string_view actionName, std::string_view keyName, uint16_t modifiers, bool onRelease)
{
    hotkeyHandler.registerBinding(state, actionName, keyName, modifiers, onRelease);
}

void InputProcessor::registerMouseButtonBinding(std::string_view state, std::string_view actionName, std::string_view buttonName, uint16_t modifiers, bool onRelease)
{
    mouseHandler.registerBinding(state, actionName, buttonName, modifiers, onRelease);
}

void InputProcessor::registerMouseMoveCallback(const std::string& state, std::function<void(int, int)> callback)
{
    mouseHandler.registerMoveCallback(state, std::move(callback));
}

void InputProcessor::registerMouseWheelCallback(const std::string& state, std::function<void(float, float)> callback)
{
    mouseHandler.registerWheelCallback(state, std::move(callback));
}

void InputProcessor::addHandler(IInputHandler *handler)
{
    handlers.push_back(handler);
}

void InputProcessor::setState(const std::string &newState)
{
    stateManager.setState(newState);
}

const std::string &InputProcessor::getCurrentState() const
{
    return stateManager.getCurrentState();
}

// --- Configuration Management ---
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <set>

using json = nlohmann::json;

namespace
{
    // Улучшенная версия, сохраняющая Left/Right
    std::vector<std::string> modifiersToStrings(uint16_t modifiers)
    {
        std::vector<std::string> mods;
        if (modifiers & Modifier::LeftCtrl) mods.push_back("LeftCtrl");
        if (modifiers & Modifier::RightCtrl) mods.push_back("RightCtrl");
        if (modifiers & Modifier::LeftShift) mods.push_back("LeftShift");
        if (modifiers & Modifier::RightShift) mods.push_back("RightShift");
        if (modifiers & Modifier::LeftAlt) mods.push_back("LeftAlt");
        if (modifiers & Modifier::RightAlt) mods.push_back("RightAlt");
        if (modifiers & Modifier::LeftSuper) mods.push_back("LeftSuper");
        if (modifiers & Modifier::RightSuper) mods.push_back("RightSuper");
        return mods;
    }

    // Улучшенная версия, читающая Left/Right
    uint16_t stringsToModifiers(const std::vector<std::string> &mods)
    {
        uint16_t result = Modifier::None;
        for (const auto &mod_str : mods)
        {
            if (mod_str == "LeftCtrl") result |= Modifier::LeftCtrl;
            else if (mod_str == "RightCtrl") result |= Modifier::RightCtrl;
            else if (mod_str == "LeftShift") result |= Modifier::LeftShift;
            else if (mod_str == "RightShift") result |= Modifier::RightShift;
            else if (mod_str == "LeftAlt") result |= Modifier::LeftAlt;
            else if (mod_str == "RightAlt") result |= Modifier::RightAlt;
            else if (mod_str == "LeftSuper") result |= Modifier::LeftSuper;
            else if (mod_str == "RightSuper") result |= Modifier::RightSuper;
            // Для обратной совместимости с "Ctrl", "Shift" и т.д.
            else if (mod_str == "Ctrl") result |= Modifier::Ctrl;
            else if (mod_str == "Shift") result |= Modifier::Shift;
            else if (mod_str == "Alt") result |= Modifier::Alt;
            else if (mod_str == "Super") result |= Modifier::Super;
        }
        return result;
    }
}

nlohmann::json InputProcessor::exportConfiguration() const
{
    std::set<std::string> all_states;
    for (const auto& state : hotkeyHandler.getRegisteredStates()) {
        all_states.insert(state);
    }
    for (const auto& state : mouseHandler.getRegisteredStates()) {
        all_states.insert(state);
    }

    json root_json;
    for (const auto& state : all_states)
    {
        json state_json;
        json kb_bindings;
        json mouse_bindings;

        for (const auto &actionName : getActionNames())
        {
            if (auto binding = hotkeyHandler.findBindingForAction(actionName, state))
            {
                json b;
                b["key"] = KeytoString(binding->key);
                b["modifiers"] = ::modifiersToStrings(binding->modifiers);
                kb_bindings[actionName] = b;
            }
            if (auto binding = mouseHandler.findBindingForAction(actionName, state))
            {
                json b;
                b["button"] = MouseButtonToString(binding->button);
                b["modifiers"] = ::modifiersToStrings(binding->modifiers);
                mouse_bindings[actionName] = b;
            }
        }
        state_json["keyboard_bindings"] = kb_bindings;
        state_json["mouse_bindings"] = mouse_bindings;
        root_json[state] = state_json;
    }
    return root_json;
}

void InputProcessor::importConfiguration(const nlohmann::json& config)
{
    for (const auto& [state_name, state_bindings] : config.items())
    {
        if (state_bindings.contains("keyboard_bindings"))
        {
            for (const auto& [actionName, info] : state_bindings["keyboard_bindings"].items()) {
                uint16_t mods = info.contains("modifiers") ? ::stringsToModifiers(info["modifiers"].get<std::vector<std::string>>()) : Modifier::None;
                registerKeyBinding(state_name, actionName, info["key"].get<std::string>(), mods);
            }
        }
        if (state_bindings.contains("mouse_bindings"))
        {
            for (const auto& [actionName, info] : state_bindings["mouse_bindings"].items()) {
                uint16_t mods = info.contains("modifiers") ? ::stringsToModifiers(info["modifiers"].get<std::vector<std::string>>()) : Modifier::None;
                registerMouseButtonBinding(state_name, actionName, info["button"].get<std::string>(), mods);
            }
        }
    }
}