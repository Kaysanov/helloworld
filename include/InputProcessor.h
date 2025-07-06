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

    void addHandler(std::shared_ptr<IInputHandler> handler);
    void removeHandler(std::shared_ptr<IInputHandler> handler);

    InputStateManager &getStateManager();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};