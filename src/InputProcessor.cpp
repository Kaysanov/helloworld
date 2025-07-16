#include "InputProcessor.h"

#include <algorithm>

#include <fmt/core.h>

InputProcessor::InputProcessor()
{
    addHandler(&hotkeyHandler);
    addHandler(&mouseHandler);

    // Настраиваем горячие клавиши

    hotkeyHandler.registerAction(
        "Default",
        "Z",
        Modifier::Ctrl,
        []()
        {
            fmt::print("{}", "Ctrl+Z Release Undo action\n");
        },
        true // On release
    );

    // mouseHandler->registerClickAction(
    mouseHandler.registerAction(
        "Default",      // Состояние
        "Left",         // Кнопка мыши
        Modifier::None, // Модификаторы (Ctrl, Shift и т.д.)
        []()            // Обработчик
        {
            fmt::print("{}", "Left mouse button clicked!\n");
        },
        false // onRelease: false = нажатие, true = отпускание
    );

    // mouseHandler->registerClickAction(
    mouseHandler.registerAction(
        "Edit",
        "Right",
        Modifier::Ctrl,
        []()
        {
            fmt::print("{}", "Ctrl+Right click in Edit mode\n");
        },
        false);

    /*mouseHandler.registerMoveCallback(
        "Default",
        [](int x, int y)
        {
            fmt::print("mouse move {} {}\n", x, y);
        });*/
}

void InputProcessor::handleEvent(const InputEvent &event)
{
    stateManager.updateFromEvent(event);

    // Создаем копию для безопасной итерации
    // auto handlers = impl_->handlers;

    for (auto &handler : handlers)
    {
        handler->handleEvent(event);
    }
}

void InputProcessor::addHandler(IInputHandler *handler)
{
    handlers.push_back(handler);
}

/*void InputProcessor::removeHandler(IInputHandler *handler)
{
    auto &handlers = impl_->handlers;
    handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
}*/

InputStateManager &InputProcessor::getStateManager()
{
    return stateManager;
}

void InputProcessor::registerAction(const std::string &state,
                                    Key key,
                                    uint16_t modifiers,
                                    std::function<void()> callback,
                                    bool onRelease)
{
    hotkeyHandler.registerAction(state, key, modifiers, callback, onRelease);
}
void InputProcessor::registerAction(const std::string &state,
                                    MouseButton button,
                                    uint16_t modifiers,
                                    std::function<void()> callback,
                                    bool onRelease)
{
    mouseHandler.registerAction(state, button, modifiers, callback, onRelease);
}