#include "InputProcessor.h"
#include "InputStateManager.h"
#include <algorithm>
#include "HotkeyHandler.h"
#include "MouseHandler.h"
#include <fmt/core.h>

struct InputProcessor::Impl
{
    InputStateManager stateManager;
    std::vector<IInputHandler *> handlers;
};

InputProcessor::InputProcessor() : impl_(std::make_unique<Impl>())
{
    HotkeyHandler *hotkeyHandler = new HotkeyHandler(getStateManager());
    MouseHandler *mouseHandler = new MouseHandler(getStateManager());

    addHandler(hotkeyHandler);
    addHandler(mouseHandler);

    // Настраиваем горячие клавиши
    hotkeyHandler->registerAction(
        "Default",
        Key::S,
        Modifier::Ctrl,
        []()
        {
            fmt::print("{}", "Ctrl+S pressed! Saving...\n");
        });
    hotkeyHandler->registerAction(
        "Default",
        Key::F1,
        Modifier::None,
        [&]()
        {
            fmt::print("{}", "F1 pressed! Перевод в state \"Edit\"...\n");
            getStateManager().setState("Edit");
        });
    hotkeyHandler->registerAction(
        "Edit",
        Key::F1,
        Modifier::None,
        [&]()
        {
            fmt::print("{}", "F1 pressed! Перевод в state \"Default\"...\n");
            getStateManager().setState("Default");
        });

    hotkeyHandler->registerAction(
        "Default",
        Key::Z,
        Modifier::Ctrl,
        []()
        {
            fmt::print("{}", "Ctrl+Z Release Undo action\n");
        },
        true // On release
    );

    mouseHandler->registerClickAction(
        "Default",         // Состояние
        MouseButton::Left, // Кнопка мыши
        Modifier::None,    // Модификаторы (Ctrl, Shift и т.д.)
        []()               // Обработчик
        {
            fmt::print("{}", "Left mouse button clicked!\n");
        },
        false // onRelease: false = нажатие, true = отпускание
    );

    mouseHandler->registerClickAction(
        "Edit",
        MouseButton::Right,
        Modifier::Ctrl,
        []()
        {
            fmt::print("{}", "Ctrl+Right click in Edit mode\n");
        },
        false);

    mouseHandler->registerMoveCallback(
        "Default",
        [](int x, int y)
        {
            fmt::print("mouse move {} {}\n", x, y);
        });
}

InputProcessor::~InputProcessor()
{
    for (auto &handler : impl_->handlers)
    {
        if (handler)
        {
            delete handler;
        }
    }
};

void InputProcessor::handleEvent(const InputEvent &event)
{
    impl_->stateManager.updateFromEvent(event);

    // Создаем копию для безопасной итерации
    // auto handlers = impl_->handlers;

    for (auto &handler : impl_->handlers)
    {
        handler->handleEvent(event);
    }
}

void InputProcessor::addHandler(IInputHandler *handler)
{
    impl_->handlers.push_back(handler);
}

/*void InputProcessor::removeHandler(IInputHandler *handler)
{
    auto &handlers = impl_->handlers;
    handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
}*/

InputStateManager &InputProcessor::getStateManager()
{
    return impl_->stateManager;
}