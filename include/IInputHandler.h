#pragma once
#include "InputTypes.h"

class IInputHandler {
public:
    virtual ~IInputHandler() = default;
    virtual void handleEvent(const InputEvent& event) = 0;
};
