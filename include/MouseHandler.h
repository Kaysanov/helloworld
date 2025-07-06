#pragma once
#include "IInputHandler.h"
#include "InputStateManager.h"
#include <functional>
#include <map>

class MouseHandler : public IInputHandler
{
public:
    struct MouseHotkey
    {
        MouseButton button;
        uint16_t modifiers;

        bool operator<(const MouseHotkey &other) const
        {
            return std::tie(button, modifiers) < std::tie(other.button, other.modifiers);
        }
    };

    explicit MouseHandler(InputStateManager &stateManager);
    void handleEvent(const InputEvent &event) override;

    void registerMoveCallback(std::function<void(int, int)> callback);
    void registerWheelCallback(std::function<void(float, float)> callback);

    void registerClickAction(
        const std::string& state,
        MouseButton button,
        uint16_t modifiers,
        std::function<void()> callback,
        bool onRelease = false);

private:
    InputStateManager &stateManager_;
    std::function<void(int, int)> moveCallback_;
    std::function<void(float, float)> wheelCallback_;
    
    std::map<std::string, std::map<MouseHotkey, std::function<void()>>> pressActions_;
    std::map<std::string, std::map<MouseHotkey, std::function<void()>>> releaseActions_;

    static MouseHotkey createHotkey(const InputEvent &event);
};