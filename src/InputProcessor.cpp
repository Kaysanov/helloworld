#include "InputProcessor.h"
#include <utility>

InputProcessor::InputProcessor()
    : hotkeyHandler(*this, stateManager), mouseHandler(*this, stateManager)
{
    addHandler(&hotkeyHandler);
    addHandler(&mouseHandler);
}

void InputProcessor::handleEvent(const InputEvent &event)
{
    stateManager.updateFromEvent(event);

    for (auto handler : handlers)
    {
        handler->handleEvent(event);
    }
}


void InputProcessor::defineAction(const std::string &name, std::function<void()> callback)
{
    actionMap_[name] = std::move(callback);
}

void InputProcessor::defineActions(const ActionMap &actions)
{
    for (const auto &pair : actions)
    {
        defineAction(pair.first, pair.second);
    }
}

void InputProcessor::triggerAction(const std::string &actionName)
{
    auto it = actionMap_.find(actionName);
    if (it != actionMap_.end() && it->second)
    {
        it->second(); // Выполняем колбэк
    }
    // Можно добавить логирование, если действие не найдено
}

std::vector<std::string> InputProcessor::getActionNames() const
{
    std::vector<std::string> names;
    names.reserve(actionMap_.size());
    for (const auto &pair : actionMap_)
    {
        names.push_back(pair.first);
    }
    return names;
}

void InputProcessor::registerKeyBinding(const std::string &state, const std::string &actionName, const std::string &keyName, uint16_t modifiers, bool onRelease)
{
    hotkeyHandler.registerBinding(state, actionName, keyName, modifiers, onRelease);
}

void InputProcessor::registerMouseButtonBinding(const std::string &state, const std::string &actionName, const std::string &buttonName, uint16_t modifiers, bool onRelease)
{
    mouseHandler.registerBinding(state, actionName, buttonName, modifiers, onRelease);
}

void InputProcessor::addHandler(IInputHandler *handler)
{
    handlers.push_back(handler);
}

void InputProcessor::setState(const std::string &newState)
{
    stateManager.setState(newState);
}

const std::string &InputProcessor::getCurrentState() const
{
    return stateManager.getCurrentState();
}