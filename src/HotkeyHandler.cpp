#include "HotkeyHandler.h"
#include "InputProcessor.h"
#include <fmt/core.h>
#include <utility>

HotkeyHandler::HotkeyHandler(InputProcessor& processor, InputStateManager &stateManager) 
    : processor_(processor), stateManager_(stateManager) {}

void HotkeyHandler::handleEvent(const InputEvent &event)
{
    if (event.type != InputEventType::KeyPressed && event.type != InputEventType::KeyReleased)
    {
        return;
    }

    const std::string &currentState = stateManager_.getCurrentState();
    auto it = actions_.find(currentState);
    if (it == actions_.end())
    {
        return; // No actions for this state
    }

    Hotkey hotkey = createHotkey(event);
    auto &stateActions = it->second;

    const auto &actionsMap = (event.type == InputEventType::KeyPressed)
                                 ? stateActions.pressActions
                                 : stateActions.releaseActions;

    auto action_it = actionsMap.find(hotkey);
    if (action_it != actionsMap.end())
    {
        processor_.triggerAction(action_it->second); // Trigger action by name
    }
}

void HotkeyHandler::registerBinding(
    std::string_view state,
    std::string_view actionName,
    std::string_view keyName,
    uint16_t modifiers,
    bool onRelease)
{
    Key key = KeyfromString(keyName);
    if (key != Key::Unknown)
    {
        registerBinding(state, actionName, key, modifiers, onRelease);
    }
    else
    {
        fmt::print(stderr, "Warning: Unknown key '{}' for binding to action '{}'.\n", keyName, actionName);
    }
}

void HotkeyHandler::registerBinding(
    std::string_view state,
    std::string_view actionName,
    Key key, 
    uint16_t modifiers, 
    bool onRelease)
{
    if (onRelease)
    {
        actions_[std::string(state)].releaseActions[{key, modifiers}] = std::string(actionName);
    }
    else
    {
        actions_[std::string(state)].pressActions[{key, modifiers}] = std::string(actionName);
    }
}

std::optional<HotkeyHandler::Hotkey> HotkeyHandler::findBindingForAction(const std::string& actionName, const std::string& state) const
{
    auto state_it = actions_.find(state);
    if (state_it == actions_.end()) {
        return std::nullopt;
    }

    // Check press actions
    for (const auto& [hotkey, name] : state_it->second.pressActions) {
        if (name == actionName) {
            return hotkey;
        }
    }

    // Check release actions
    for (const auto& [hotkey, name] : state_it->second.releaseActions) {
        if (name == actionName) {
            return hotkey;
        }
    }

    return std::nullopt;
}

std::vector<std::string> HotkeyHandler::getRegisteredStates() const
{
    std::vector<std::string> states;
    states.reserve(actions_.size());
    for (const auto& [state, _] : actions_)
    {
        states.push_back(state);
    }
    return states;
}


HotkeyHandler::Hotkey HotkeyHandler::createHotkey(const InputEvent &event)
{
    return {event.data.key.key, event.data.key.modifiers};
}
