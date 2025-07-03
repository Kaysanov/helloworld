#include "InputState.h"
#include <SDL3/SDL.h>

InputState &InputState::get_instance()
{
    static InputState instance;
    return instance;
}

void InputState::handle_event(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        mouse_x = event->motion.x;
        mouse_y = event->motion.y;
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        mouse_buttons |= SDL_BUTTON_MASK(event->button.button);
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        mouse_buttons &= ~SDL_BUTTON_MASK(event->button.button);
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        wheel_x = event->wheel.x;
        wheel_y = event->wheel.y;
        break;
    }
}

void InputState::update()
{
    wheel_x = 0;
    wheel_y = 0;
}

bool InputState::is_key_pressed(SDL_Keycode key) const
{
    const SDL_Scancode scancode = SDL_GetScancodeFromKey(key, NULL);
    const bool *state = SDL_GetKeyboardState(nullptr);
    return state[scancode];
}

bool InputState::is_mouse_button_pressed(Uint8 button) const
{
    return (mouse_buttons & SDL_BUTTON_MASK(button)) != 0;
}

std::pair<int, int> InputState::get_mouse_position() const
{
    return {mouse_x, mouse_y};
}

Uint32 InputState::get_mouse_buttons() const
{
    return mouse_buttons;
}

void InputState::get_mouse_wheel(float &x, float &y) const
{
    x = wheel_x;
    y = wheel_y;
}