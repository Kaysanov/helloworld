#pragma once
#include <vector>
#include <memory>

#include "IInputHandler.h"
#include "InputStateManager.h"
#include "HotkeyHandler.h"
#include "MouseHandler.h"

class InputProcessor : public IInputHandler
{
public:
    InputProcessor();
    ~InputProcessor() = default;

    void handleEvent(const InputEvent &event) override;

    InputStateManager &getStateManager();
    HotkeyHandler getHotkeyHandler() { return hotkeyHandler; };
    MouseHandler getMouseHandler() { return mouseHandler; };
    
    void registerAction(const std::string &state,
                        Key key,
                        uint16_t modifiers,
                        std::function<void()> callback,
                        bool onRelease = false);

    void registerAction(const std::string &state,
                        MouseButton button,
                        uint16_t modifiers,
                        std::function<void()> callback,
                        bool onRelease = false);

private:
    void addHandler(IInputHandler *handler);
    // void removeHandler(IInputHandler *handler);

private:
    InputStateManager stateManager;
    std::vector<IInputHandler *> handlers;
    HotkeyHandler hotkeyHandler{stateManager};
    MouseHandler mouseHandler{stateManager};
};