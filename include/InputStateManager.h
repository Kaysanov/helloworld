#pragma once
#include "InputTypes.h"
#include <unordered_map>
#include <vector>

class InputStateManager
{
public:
    void updateFromEvent(const InputEvent &event);

    // Управление состояниями
    void setState(InputState newState);
    InputState getCurrentState() const;
    void pushState(InputState newState);
    void popState();

    // Проверка состояний ввода
    bool isKeyPressed(Key key) const;
    bool isMouseButtonPressed(MouseButton button) const;

private:
    InputState currentState_ = InputState::Default;
    std::vector<InputState> stateStack_;
    std::unordered_map<Key, bool> keyStates_;
    std::unordered_map<MouseButton, bool> mouseButtonStates_;
};
