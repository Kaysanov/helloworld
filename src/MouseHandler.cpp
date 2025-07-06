#include "MouseHandler.h"

void MouseHandler::registerMoveCallback(std::function<void(int, int)> callback) {
    moveCallback_ = callback;
}

void MouseHandler::registerWheelCallback(std::function<void(float, float)> callback) {
    wheelCallback_ = callback;
}

void MouseHandler::registerClickCallback(MouseButton button, std::function<void()> callback) {
    clickCallbacks_[button] = callback;
}

void MouseHandler::handleEvent(const InputEvent& event) {
    switch (event.type) {
        case InputEventType::MouseMoved:
            if (moveCallback_) {
                moveCallback_(event.data.mouseMove.x, event.data.mouseMove.y);
            }
            break;
            
        case InputEventType::MouseWheel:
            if (wheelCallback_) {
                wheelCallback_(event.data.mouseWheel.x, event.data.mouseWheel.y);
            }
            break;
            
        case InputEventType::MouseButtonPressed:
            if (auto it = clickCallbacks_.find(event.data.mouseButton.button); 
                it != clickCallbacks_.end() && it->second) {
                it->second();
            }
            break;
            
        default:
            // Игнорируем другие события
            break;
    }
}