#pragma once
#include "InputSystem.h"
#include <SDL3/SDL.h>
#include <vector>

class SDLInputSystem : public InputSystem
{
public:
    SDLInputSystem();
    ~SDLInputSystem();

    bool initialize() override;
    void shutdown() override;

    void pollEvents() override;
    const std::vector<InputEvent> &getEvents() const override;

    bool isKeyPressed(Key key) const override;
    bool isMouseButtonPressed(MouseButton button) const override;
    MousePosition getMousePosition() const override;

    void *createWindow(const char *title, int width, int height) override;
    void destroyWindow(void *window) override;

private:
    SDL_Window *window = nullptr;
    std::vector<InputEvent> events;

    Key convertSDLKey(SDL_Keycode sdlKey) const;
    MouseButton convertSDLMouseButton(Uint8 button) const;
    uint16_t convertSDLModifiers(SDL_Keymod mods) const;
};