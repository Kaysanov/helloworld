#pragma once
#include "InputTypes.h"
#include <unordered_map>
#include <vector>
#include <string>  

class InputStateManager
{
public:
    void updateFromEvent(const InputEvent &event);

    // Управление состояниями
    void setState(const std::string& newState);
    const std::string& getCurrentState() const;
    //void pushState(const std::string& newState);
    //void popState();

    // Проверка состояний ввода
    bool isKeyPressed(Key key) const;
    bool isMouseButtonPressed(MouseButton button) const;
    uint16_t getModifiers() const;

private:
    std::string currentState_ = "Default";
    //std::vector<std::string> stateStack_;
    std::unordered_map<Key, bool> keyStates_;
    std::unordered_map<MouseButton, bool> mouseButtonStates_;
};
