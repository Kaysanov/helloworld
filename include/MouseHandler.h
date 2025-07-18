#pragma once
#include "IInputHandler.h"
#include "InputStateManager.h"
#include <functional>
#include <map>

class MouseHandler : public InputActionHandler
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

    void registerMoveCallback(const std::string &state, std::function<void(int, int)> callback);
    void registerWheelCallback(const std::string &state, std::function<void(float, float)> callback);

    // Унифицированный метод регистрации
    void registerAction(const std::string &state,
                        const std::string &buttonName, // Имя кнопки вместо enum
                        uint16_t modifiers,
                        std::function<void()> callback,
                        bool onRelease = false) override;

    // private:
    void registerAction(const std::string &state,
                        MouseButton button,
                        uint16_t modifiers,
                        std::function<void()> callback,
                        bool onRelease = false);

    InputStateManager &stateManager_;

    std::map<std::string, std::function<void(int, int)>> moveCallbacks_;
    std::map<std::string, std::function<void(float, float)>> wheelCallbacks_;

    std::map<std::string, std::map<MouseHotkey, std::function<void()>>> pressActions_;
    std::map<std::string, std::map<MouseHotkey, std::function<void()>>> releaseActions_;

    static MouseHotkey createHotkey(const InputEvent &event);
};