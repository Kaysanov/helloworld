#include "MouseHandler.h"
#include "InputProcessor.h"
#include <fmt/core.h>
#include <utility>

MouseHandler::MouseHandler(InputProcessor& processor, InputStateManager &stateManager) 
    : processor_(processor), stateManager_(stateManager) {}

void MouseHandler::handleEvent(const InputEvent &event)
{
    const std::string &currentState = stateManager_.getCurrentState();

    switch (event.type)
    {
    case InputEventType::MouseButtonPressed:
    case InputEventType::MouseButtonReleased:
    {
        auto &actionsMap = (event.type == InputEventType::MouseButtonPressed) ? pressActions_ : releaseActions_;
        if (actionsMap.count(currentState))
        {
            MouseHotkey hotkey = createHotkey(event);
            auto &stateActions = actionsMap.at(currentState);
            auto action_it = stateActions.find(hotkey);
            if (action_it != stateActions.end())
            {
                processor_.triggerAction(action_it->second); // Trigger by name
            }
        }
        break;
    }
    case InputEventType::MouseMoved:
    {
        auto it = moveCallbacks_.find(currentState);
        if (it != moveCallbacks_.end() && it->second)
        {
            it->second(event.data.mouseMove.x, event.data.mouseMove.y);
        }
        break;
    }
    case InputEventType::MouseWheel:
    {
        auto it = wheelCallbacks_.find(currentState);
        if (it != wheelCallbacks_.end() && it->second)
        {
            it->second(event.data.mouseWheel.x, event.data.mouseWheel.y);
        }
        break;
    }
    default:
        break;
    }
}

void MouseHandler::registerMoveCallback(const std::string &state, std::function<void(int, int)> callback)
{
    moveCallbacks_[state] = std::move(callback);
}

void MouseHandler::registerWheelCallback(const std::string &state, std::function<void(float, float)> callback)
{
    wheelCallbacks_[state] = std::move(callback);
}

void MouseHandler::registerBinding(const std::string &state,
                                   const std::string &actionName,
                                   const std::string &buttonName,
                                   uint16_t modifiers,
                                   bool onRelease)
{
    MouseButton button = MouseButtonfromString(buttonName);
    if (button != MouseButton::None)
    {
        registerBinding(state, actionName, button, modifiers, onRelease);
    }
    else
    {
        fmt::print(stderr, "Warning: Unknown mouse button '{}' for binding to action '{}'.\n", buttonName, actionName);
    }
}

void MouseHandler::registerBinding(const std::string &state,
                                   const std::string &actionName,
                                   MouseButton button,
                                   uint16_t modifiers,
                                   bool onRelease)
{
    if (onRelease)
    {
        releaseActions_[state][{button, modifiers}] = actionName;
    }
    else
    {
        pressActions_[state][{button, modifiers}] = actionName;
    }
}

std::optional<MouseHandler::MouseHotkey> MouseHandler::findBindingForAction(const std::string& actionName, const std::string& state) const
{
    // Check press actions
    auto press_it = pressActions_.find(state);
    if (press_it != pressActions_.end()) {
        for (const auto& [hotkey, name] : press_it->second) {
            if (name == actionName) {
                return hotkey;
            }
        }
    }

    // Check release actions
    auto release_it = releaseActions_.find(state);
    if (release_it != releaseActions_.end()) {
        for (const auto& [hotkey, name] : release_it->second) {
            if (name == actionName) {
                return hotkey;
            }
        }
    }

    return std::nullopt;
}

MouseHandler::MouseHotkey MouseHandler::createHotkey(const InputEvent &event)
{
    return {event.data.mouseButton.button, event.data.mouseButton.modifiers};
}
