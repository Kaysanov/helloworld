#pragma once
#include "InputTypes.h"
#include <string>
#include <functional>

class IInputHandler
{
public:
    virtual ~IInputHandler() = default;
    virtual void handleEvent(const InputEvent &event) = 0;
};

class InputActionHandler : public IInputHandler
{
public:
    virtual ~InputActionHandler() = default;

    virtual void registerAction(
        const std::string &state,
        const std::string &inputId, // Универсальный идентификатор ввода
        uint16_t modifiers,
        std::function<void()> callback,
        bool onRelease = false) = 0;
};

