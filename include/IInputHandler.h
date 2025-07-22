#pragma once
#include "InputTypes.h"
#include <string>
#include <string_view>
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

    // Renamed to be more descriptive. Binds an input to a named action.
    virtual void registerBinding(
        std::string_view state,
        std::string_view actionName,
        std::string_view inputId, // Универсальный идентификатор ввода
        uint16_t modifiers,
        bool onRelease = false) = 0;
};
