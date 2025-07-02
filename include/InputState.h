#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <SDL3/SDL.h>
#include <unordered_map>

class InputState
{
public:
    void updateFromEvent(const SDL_Event *event);
    void resetFrameState();

    bool isKeyPressed(SDL_Keycode key) const;
    bool isMouseButtonPressed(Uint8 button) const;
    std::pair<int, int> getMousePosition() const;
    std::pair<float, float> getMouseWheel() const;

private:
    mutable std::unordered_map<SDL_Keycode, SDL_Scancode> keycodeToScancode;
    SDL_Scancode getScancode(SDL_Keycode key) const;

    const bool *keyboardState = nullptr;
    int mouseX = 0;
    int mouseY = 0;
    Uint32 mouseButtons = 0;
    float wheelX = 0;
    float wheelY = 0;
};

#endif // INPUTSTATE_H