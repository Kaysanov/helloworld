#include "InputStateManager.h"

void InputStateManager::updateFromEvent(const InputEvent &event)
{
    switch (event.type)
    {
    case InputEventType::KeyPressed:
        keyStates_[event.data.key.key] = true;
        break;
    case InputEventType::KeyReleased:
        keyStates_[event.data.key.key] = false;
        break;
    case InputEventType::MouseButtonPressed:
        mouseButtonStates_[event.data.mouseButton.button] = true;
        break;
    case InputEventType::MouseButtonReleased:
        mouseButtonStates_[event.data.mouseButton.button] = false;
        break;
    default:
        break;
    }
}

void InputStateManager::setState(const std::string& newState)
{
    currentState_ = newState;
}

const std::string& InputStateManager::getCurrentState() const
{
    return currentState_;
}

void InputStateManager::pushState(const std::string& newState)
{
    stateStack_.push_back(currentState_);
    currentState_ = newState;
}

void InputStateManager::popState()
{
    if (!stateStack_.empty())
    {
        currentState_ = stateStack_.back();
        stateStack_.pop_back();
    }
}

bool InputStateManager::isKeyPressed(Key key) const
{
    auto it = keyStates_.find(key);
    return it != keyStates_.end() && it->second;
}

bool InputStateManager::isMouseButtonPressed(MouseButton button) const
{
    auto it = mouseButtonStates_.find(button);
    return it != mouseButtonStates_.end() && it->second;
}