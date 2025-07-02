#include "InputState.h"

void InputState::updateFromEvent(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        mouseX = event->motion.x;
        mouseY = event->motion.y;
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        mouseButtons |= SDL_BUTTON_MASK(event->button.button);
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        mouseButtons &= ~SDL_BUTTON_MASK(event->button.button);
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        wheelX = event->wheel.x;
        wheelY = event->wheel.y;
        break;
    }
}

void InputState::resetFrameState()
{
    wheelX = 0;
    wheelY = 0;
    keyboardState = SDL_GetKeyboardState(nullptr);
}

bool InputState::isKeyPressed(SDL_Keycode key) const
{
    SDL_Scancode scancode = getScancode(key);
    return keyboardState[scancode];
}

bool InputState::isMouseButtonPressed(Uint8 button) const
{
    return (mouseButtons & SDL_BUTTON_MASK(button)) != 0;
}

std::pair<int, int> InputState::getMousePosition() const
{
    return {mouseX, mouseY};
}

std::pair<float, float> InputState::getMouseWheel() const
{
    return {wheelX, wheelY};
}

SDL_Scancode InputState::getScancode(SDL_Keycode key) const
{
    auto it = keycodeToScancode.find(key);
    if (it != keycodeToScancode.end())
    {
        return it->second;
    }

    SDL_Keymod dummy;
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, &dummy);
    keycodeToScancode[key] = scancode;
    return scancode;
}