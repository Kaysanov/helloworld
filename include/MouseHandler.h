#pragma once
#include "IInputHandler.h"
#include "InputStateManager.h"
#include <map>
#include <string>
#include <functional>
#include <optional>

// Forward declaration to break circular dependency
class InputProcessor;
class MouseHandler : public InputActionHandler
{
public:
   struct MouseHotkey
    {
        MouseButton button;
        uint16_t modifiers;

        // operator< необходим для использования в std::map
        bool operator<(const MouseHotkey &other) const
        {
            if (button != other.button)
            {
                return button < other.button;
            }
            return modifiers < other.modifiers;
        }
    };

    explicit MouseHandler(InputProcessor& processor, InputStateManager &stateManager);
    void handleEvent(const InputEvent &event) override;

    void registerMoveCallback(const std::string &state, std::function<void(int, int)> callback);
    void registerWheelCallback(const std::string &state, std::function<void(float, float)> callback);

    // Binds a mouse button to a named action.
    void registerBinding(const std::string &state,
                        const std::string &actionName,
                        const std::string &buttonName, // Имя кнопки вместо enum
                        uint16_t modifiers,
                        bool onRelease = false) override;

    // Finds the mouse binding for a given action in a specific state.
    std::optional<MouseHotkey> findBindingForAction(const std::string& actionName, const std::string& state) const;

private:
    void registerBinding(const std::string &state,
                         const std::string &actionName,
                         MouseButton button,
                         uint16_t modifiers,
                         bool onRelease = false);

    InputProcessor& processor_;
    InputStateManager &stateManager_;

    std::map<std::string, std::function<void(int, int)>> moveCallbacks_;
    std::map<std::string, std::function<void(float, float)>> wheelCallbacks_;

    std::map<std::string, std::map<MouseHotkey, std::string>> pressActions_;
    std::map<std::string, std::map<MouseHotkey, std::string>> releaseActions_;

    static MouseHotkey createHotkey(const InputEvent &event);
};
