#pragma once
#include "InputTypes.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include "InputProcessor.h"

class SDL3EventGenerator
{
public:
    std::vector<InputEvent> processSDLEvents() const;
    void runEventLoop(InputProcessor &processor);

private:
    InputEvent convertSDLEvent(const SDL_Event &event) const;
    Key convertSDLKey(SDL_Keycode key) const;
    MouseButton convertSDLMouseButton(Uint32 button) const;
    uint16_t convertSDLModifiers(Uint32 mod) const;
};

