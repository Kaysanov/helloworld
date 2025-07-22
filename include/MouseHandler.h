#pragma once
#include "IInputHandler.h"
#include "InputStateManager.h"
#include <unordered_map>
#include <string_view>
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

        bool operator==(const MouseHotkey &other) const
        {
            return button == other.button && modifiers == other.modifiers;
        }
    };

    struct MouseHotkeyHash
    {
        std::size_t operator()(const MouseHotkey &h) const
        {
            // Простая комбинация хэшей, аналогично HotkeyHandler
            return std::hash<int>()(static_cast<int>(h.button)) ^ (std::hash<uint16_t>()(h.modifiers) << 1);
        }
    };

    explicit MouseHandler(InputProcessor& processor, InputStateManager &stateManager);
    void handleEvent(const InputEvent &event) override;

    void registerMoveCallback(const std::string &state, std::function<void(int, int)> callback);
    void registerWheelCallback(const std::string &state, std::function<void(float, float)> callback);

    // Binds a mouse button to a named action.
    void registerBinding(std::string_view state,
                        std::string_view actionName,
                        std::string_view buttonName, // Имя кнопки вместо enum
                        uint16_t modifiers,
                        bool onRelease = false) override;

    // Finds the mouse binding for a given action in a specific state.
    std::optional<MouseHotkey> findBindingForAction(const std::string& actionName, const std::string& state) const;

    // Returns a list of all states that have bindings registered.
    std::vector<std::string> getRegisteredStates() const;

private:
    void registerBinding(std::string_view state,
                         std::string_view actionName,
                         MouseButton button,
                         uint16_t modifiers,
                         bool onRelease = false);

    InputProcessor& processor_;
    InputStateManager &stateManager_;

    std::unordered_map<std::string, std::function<void(int, int)>> moveCallbacks_;
    std::unordered_map<std::string, std::function<void(float, float)>> wheelCallbacks_;

    std::unordered_map<std::string, std::unordered_map<MouseHotkey, std::string, MouseHotkeyHash>> pressActions_;
    std::unordered_map<std::string, std::unordered_map<MouseHotkey, std::string, MouseHotkeyHash>> releaseActions_;

    static MouseHotkey createHotkey(const InputEvent &event);
};
