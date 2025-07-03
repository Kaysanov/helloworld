#include "MouseEventProcessor.h"

void MouseEventProcessor::register_motion_callback(PositionCallback callback)
{
    motion_callback = callback;
}

void MouseEventProcessor::register_wheel_callback(WheelCallback callback)
{
    wheel_callback = callback;
}

void MouseEventProcessor::register_click_callback(Uint8 button, ClickCallback callback)
{
    click_callbacks[button] = callback;
}

void MouseEventProcessor::process_event(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        if (motion_callback)
            motion_callback(event->motion.x, event->motion.y);
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    {
        auto it = click_callbacks.find(event->button.button);
        if (it != click_callbacks.end())
            it->second();
        break;
    }
    case SDL_EVENT_MOUSE_WHEEL:
        if (wheel_callback)
            wheel_callback(event->wheel.x, event->wheel.y);
        break;
    }
}