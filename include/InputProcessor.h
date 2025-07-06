#pragma once
#include "IInputHandler.h"
#include "InputTypes.h"
#include <functional>
#include <memory>

class InputProcessor {
public:
    InputProcessor();
    ~InputProcessor();
    
    void handleEvent(const InputEvent& event);
    
    // Методы для регистрации обработчиков
    void registerKeyboardHotkey(Key key, uint16_t modifiers, std::function<void()> callback);
    void registerMouseHotkey(MouseButton button, uint16_t modifiers, std::function<void()> callback);
    void registerMouseMoveCallback(std::function<void(int, int)> callback);
    void registerMouseWheelCallback(std::function<void(float, float)> callback);
    void registerClickCallback(MouseButton button, std::function<void()> callback);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};