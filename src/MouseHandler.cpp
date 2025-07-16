#include "MouseHandler.h"

MouseHandler::MouseHandler(InputStateManager &stateManager)
    : stateManager_(stateManager) {}

void MouseHandler::handleEvent(const InputEvent &event)
{
    auto state = stateManager_.getCurrentState();
    switch (event.type)
    {
    case InputEventType::MouseMoved:
        if (auto stateIt = moveCallbacks_.find(state); stateIt != moveCallbacks_.end())
        {
            stateIt->second(event.data.mouseMove.x, event.data.mouseMove.y);
        }

        break;

    case InputEventType::MouseWheel:

        if (auto stateIt = wheelCallbacks_.find(state); stateIt != wheelCallbacks_.end())
        {
            stateIt->second(event.data.mouseWheel.x, event.data.mouseWheel.y);
        }
        break;

    case InputEventType::MouseButtonPressed:
    case InputEventType::MouseButtonReleased:
    {

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

void MouseHandler::registerMoveCallback(const std::string &state, std::function<void(int, int)> callback)
{
    moveCallbacks_[state] = callback;
}

void MouseHandler::registerWheelCallback(const std::string &state, std::function<void(float, float)> callback)
{
    wheelCallbacks_[state] = callback;
}

void MouseHandler::registerAction(const std::string &state,
                                  const std::string &buttonName,
                                  uint16_t modifiers,
                                  std::function<void()> callback,
                                  bool onRelease)
{
    //MouseButton button = MouseButtonfromString(buttonName);
    registerAction(state, MouseButtonfromString(buttonName), modifiers, std::move(callback), onRelease);

    /*MouseHotkey hk{button, modifiers};
    if (onRelease)
    {
        releaseActions_[state][hk] = callback;
    }
    else
    {
        pressActions_[state][hk] = callback;
    }*/
}

void MouseHandler::registerAction(const std::string &state,
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