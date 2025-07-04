#pragma once
#include "InputTypes.h"
#include <vector>

class InputSystem {
public:
    virtual ~InputSystem() = default;
    
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    
    virtual void pollEvents() = 0;
    virtual const std::vector<InputEvent>& getEvents() const = 0;
    
    virtual bool isKeyPressed(Key key) const = 0;
    virtual bool isMouseButtonPressed(MouseButton button) const = 0;
    virtual MousePosition getMousePosition() const = 0;
    
    virtual void* createWindow(const char* title, int width, int height) = 0;
    virtual void destroyWindow(void* window) = 0;
};