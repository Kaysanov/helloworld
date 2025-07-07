#pragma once
#include "IInputHandler.h"
#include "InputStateManager.h"
#include <vector>
#include <memory>

class InputProcessor : public IInputHandler
{
public:
    InputProcessor();
    ~InputProcessor();

    void handleEvent(const InputEvent &event) override;

    InputStateManager &getStateManager();
    
private:
    void addHandler(IInputHandler *handler);
    //void removeHandler(IInputHandler *handler);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};