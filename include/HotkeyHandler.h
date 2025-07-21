#pragma once
#include "IInputHandler.h"
#include "InputStateManager.h"
#include <unordered_map>
#include <string>
#include <optional>

// Forward declaration to break circular dependency
class InputProcessor;

class HotkeyHandler : public InputActionHandler
{
public:
    struct Hotkey
    {
        Key key;
        uint16_t modifiers;

        bool operator==(const Hotkey &other) const
        {
            return key == other.key && modifiers == other.modifiers;
        }
    };

    struct HotkeyHash
    {
        std::size_t operator()(const Hotkey &h) const
        {
            // Простая комбинация хэшей
            return std::hash<int>()(static_cast<int>(h.key)) ^ (std::hash<uint16_t>()(h.modifiers) << 1);
        }
    };

    explicit HotkeyHandler(InputProcessor &processor, InputStateManager &stateManager);
    void handleEvent(const InputEvent &event) override;

    // Binds a key to a named action. The action must be defined in InputProcessor.
    void registerBinding(
        const std::string &state,
        const std::string &actionName,
        const std::string &keyName,
        uint16_t modifiers,
        bool onRelease = false) override;

    // Finds the key binding for a given action in a specific state. Used for saving configs.
    std::optional<Hotkey> findBindingForAction(const std::string &actionName, const std::string &state) const;

private:
    void registerBinding(const std::string &state, const std::string &actionName, Key key, uint16_t modifiers, bool onRelease);

    struct StateHotkeys
    {
        std::unordered_map<Hotkey, std::string, HotkeyHash> pressActions;
        std::unordered_map<Hotkey, std::string, HotkeyHash> releaseActions;
    };

    InputProcessor &processor_;
    InputStateManager &stateManager_;
    std::unordered_map<std::string, StateHotkeys> actions_;

    Hotkey createHotkey(const InputEvent &event);
};