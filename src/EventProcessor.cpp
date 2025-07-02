#include "EventProcessor.h"
#include "InputState.h"
#include "HotkeyRegistry.h"

void EventProcessor::setMouseMoveCallback(MousePositionCallback callback)
{
    mouseMoveCallback = callback;
}

void EventProcessor::setMouseWheelCallback(MouseWheelCallback callback)
{
    mouseWheelCallback = callback;
}

void EventProcessor::processEvent(const SDL_Event *event, InputState &inputState, HotkeyRegistry &registry)
{
    inputState.updateFromEvent(event);

    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        if (mouseMoveCallback)
        {
            auto [x, y] = inputState.getMousePosition();
            mouseMoveCallback(x, y);
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        registry.handleClick(event->button.button);
        break;

    case SDL_EVENT_MOUSE_WHEEL:
        if (mouseWheelCallback)
        {
            auto [x, y] = inputState.getMouseWheel();
            mouseWheelCallback(x, y);
        }
        break;
    }
}