#include "MouseHandler.h"

MouseHandler::MouseHandler(InputStateManager &stateManager)
    : stateManager_(stateManager) {}

void MouseHandler::handleEvent(const InputEvent &event)
{
    switch (event.type)
    {
    case InputEventType::MouseMoved:
        if (moveCallback_)
        {
            moveCallback_(event.data.mouseMove.x, event.data.mouseMove.y);
        }
        break;

    case InputEventType::MouseWheel:
        if (wheelCallback_)
        {
            wheelCallback_(event.data.mouseWheel.x, event.data.mouseWheel.y);
        }
        break;

    case InputEventType::MouseButtonPressed:
    case InputEventType::MouseButtonReleased:
    {
        auto state = stateManager_.getCurrentState();
        MouseHotkey hk = createHotkey(event);

        if (event.type == InputEventType::MouseButtonPressed)
        {
            if (auto stateIt = pressActions_.find(state); stateIt != pressActions_.end())
            {
                if (auto actionIt = stateIt->second.find(hk); actionIt != stateIt->second.end())
                {
                    actionIt->second();
                }
            }
        }
        else if (event.type == InputEventType::MouseButtonReleased)
        {
            if (auto stateIt = releaseActions_.find(state); stateIt != releaseActions_.end())
            {
                if (auto actionIt = stateIt->second.find(hk); actionIt != stateIt->second.end())
                {
                    actionIt->second();
                }
            }
        }
        break;
    }

    default:
        break;
    }
}

void MouseHandler::registerMoveCallback(std::function<void(int, int)> callback)
{
    moveCallback_ = callback;
}

void MouseHandler::registerWheelCallback(std::function<void(float, float)> callback)
{
    wheelCallback_ = callback;
}

void MouseHandler::registerClickAction(
    InputState state,
    MouseButton button,
    uint16_t modifiers,
    std::function<void()> callback,
    bool onRelease)
{
    MouseHotkey hk{button, modifiers};
    if (onRelease)
    {
        releaseActions_[state][hk] = callback;
    }
    else
    {
        pressActions_[state][hk] = callback;
    }
}

MouseHandler::MouseHotkey MouseHandler::createHotkey(const InputEvent &event)
{
    return {
        event.data.mouseButton.button,
        event.data.mouseButton.modifiers};
}