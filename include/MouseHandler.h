#pragma once
#include "IInputHandler.h"
#include "InputTypes.h"
#include <functional>
#include <map>

class MouseHandler : public IInputHandler {
public:
    void registerMoveCallback(std::function<void(int, int)> callback);
    void registerWheelCallback(std::function<void(float, float)> callback);
    void registerClickCallback(MouseButton button, std::function<void()> callback);
    
    void handleEvent(const InputEvent& event) override;

private:
    std::function<void(int, int)> moveCallback_;
    std::function<void(float, float)> wheelCallback_;
    std::map<MouseButton, std::function<void()>> clickCallbacks_;
};
