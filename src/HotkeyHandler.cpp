#include "HotkeyHandler.h"
#include <algorithm>

HotkeyHandler::HotkeyHandler(InputStateManager &stateManager)
    : stateManager_(stateManager) {}

void HotkeyHandler::handleEvent(const InputEvent &event)
{
    if (event.type != InputEventType::KeyPressed &&
        event.type != InputEventType::KeyReleased)
    {
        return;
    }

    auto state = stateManager_.getCurrentState();
    auto it = actions_.find(state);
    if (it == actions_.end())
        return;

    Hotkey hk = createHotkey(event);
    
    const auto &stateActions = it->second;

    if (event.type == InputEventType::KeyPressed)
    {
        if (auto callbackIt = stateActions.pressActions.find(hk);
            callbackIt != stateActions.pressActions.end())
        {
            callbackIt->second();
        }
    }
    else if (event.type == InputEventType::KeyReleased)
    {
        if (auto callbackIt = stateActions.releaseActions.find(hk);
            callbackIt != stateActions.releaseActions.end())
        {
            callbackIt->second();
        }
    }
}

void HotkeyHandler::registerAction(
    const std::string &state,
    const std::string &keyName,
    uint16_t modifiers,
    std::function<void()> callback,
    bool onRelease)
{
    Key key = KeyfromString(keyName);
    registerAction(state, key, modifiers, std::move(callback), onRelease);
}

void HotkeyHandler::registerAction(
    const std::string &state,
    Key key,
    uint16_t modifiers,
    std::function<void()> callback,
    bool onRelease)
{
    Hotkey hk{key, modifiers};
    if (onRelease)
    {
        actions_[state].releaseActions[hk] = callback;
    }
    else
    {
        actions_[state].pressActions[hk] = callback;
    }
}

HotkeyHandler::Hotkey HotkeyHandler::createHotkey(const InputEvent &event)
{
    return {event.data.key.key, stateManager_.getModifiers()};
}