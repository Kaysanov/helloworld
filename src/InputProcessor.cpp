#include "InputProcessor.h"
#include "InputStateManager.h"
#include <algorithm>

struct InputProcessor::Impl
{
    InputStateManager stateManager;
    std::vector<std::shared_ptr<IInputHandler>> handlers;
};

InputProcessor::InputProcessor() : impl_(std::make_unique<Impl>()) {}
InputProcessor::~InputProcessor() = default;

void InputProcessor::handleEvent(const InputEvent &event)
{
    impl_->stateManager.updateFromEvent(event);

    // Создаем копию для безопасной итерации
    auto handlers = impl_->handlers;

    for (auto &handler : handlers)
    {
        handler->handleEvent(event);
    }
}

void InputProcessor::addHandler(std::shared_ptr<IInputHandler> handler)
{
    impl_->handlers.push_back(handler);
}

void InputProcessor::removeHandler(std::shared_ptr<IInputHandler> handler)
{
    auto &handlers = impl_->handlers;
    handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
}

InputStateManager &InputProcessor::getStateManager()
{
    return impl_->stateManager;
}