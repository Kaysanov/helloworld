#pragma once
#include "IInputHandler.h"
#include "InputStateManager.h"
#include <functional>
#include <unordered_map>

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
    // Хеш-функция должна быть определена в заголовочном файле
    struct HotkeyHash
    {
        size_t operator()(const Hotkey &hk) const
        {
            return static_cast<size_t>(hk.key) 
                   ^ static_cast<size_t>(hk.modifiers) << 16;
        }
    };

    explicit HotkeyHandler(InputStateManager &stateManager);
    void handleEvent(const InputEvent &event) override;
// Унифицированный метод регистрации
    void registerAction(
        const std::string &state,
        const std::string &keyName, // Имя кнопки вместо enum
        uint16_t modifiers,
        std::function<void()> callback,
        bool onRelease = false) override;
private:        
    void registerAction(
        const std::string& state,
        Key key,
        uint16_t modifiers,
        std::function<void()> callback,
        bool onRelease = false);

private:
    struct StateHotkeys
    {
        std::unordered_map<Hotkey, std::function<void()>, HotkeyHash> pressActions;
        std::unordered_map<Hotkey, std::function<void()>, HotkeyHash> releaseActions;
    };

    InputStateManager &stateManager_;
    
    std::unordered_map<std::string, StateHotkeys> actions_;

    static Hotkey createHotkey(const InputEvent &event);
};