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
    ~InputProcessor();

    void handleEvent(const InputEvent &event) override;

    InputStateManager &getStateManager();
    HotkeyHandler* getHotkeyHandler() { return hotkeyHandler; };
    MouseHandler* getMouseHandler(){ return mouseHandler; };
    
private:
    void addHandler(IInputHandler *handler);
    //void removeHandler(IInputHandler *handler);

private:    
    InputStateManager stateManager;
    std::vector<IInputHandler *> handlers;
    HotkeyHandler *hotkeyHandler;
    MouseHandler *mouseHandler;
};