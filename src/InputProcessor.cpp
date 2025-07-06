#include "InputProcessor.h"
#include "HotkeyRegistry.h"
#include "MouseHandler.h"
#include <iostream>

struct InputProcessor::Impl
{
    std::unique_ptr<HotkeyRegistry> registry;
    std::unique_ptr<MouseHandler> mouseHandler;

    Impl()
        : registry(std::make_unique<HotkeyRegistry>()), mouseHandler(std::make_unique<MouseHandler>()) {}
};

InputProcessor::InputProcessor() : impl_(std::make_unique<Impl>()) {}
InputProcessor::~InputProcessor() = default;

void InputProcessor::handleEvent(const InputEvent &event)
{   
    // Обработка горячих клавиш
    if (event.type == InputEventType::KeyPressed ||
        event.type == InputEventType::MouseButtonPressed)
    {

        HotkeyRegistry::Hotkey hk;
        hk.modifiers = [&]
        {
            if (event.type == InputEventType::KeyPressed)
                return event.data.key.modifiers;
            if (event.type == InputEventType::MouseButtonPressed)
                return event.data.mouseButton.modifiers;
            return static_cast<uint16_t>(0);
        }();

        if (event.type == InputEventType::KeyPressed)
        {
            hk.type = HotkeyType::Keyboard;
            hk.input.key = event.data.key.key;
        }
        else if (event.type == InputEventType::MouseButtonPressed)
        {
            hk.type = HotkeyType::Mouse;
            hk.input.button = event.data.mouseButton.button;            
        }

        if (auto callback = impl_->registry->findCallback(hk))
        {
            std::cout << "Hotkey callback found" << std::endl;
            callback();
        }
        else
        {
            std::cout << "No callback for hotkey" << std::endl;
        }
    }

    // Передача события в обработчик мыши
    impl_->mouseHandler->handleEvent(event);
}

void InputProcessor::registerKeyboardHotkey(Key key, uint16_t modifiers, std::function<void()> callback)
{
    impl_->registry->registerKeyboardHotkey(key, modifiers, callback);
}

void InputProcessor::registerMouseHotkey(MouseButton button, uint16_t modifiers, std::function<void()> callback)
{
    impl_->registry->registerMouseHotkey(button, modifiers, callback);
}

void InputProcessor::registerMouseMoveCallback(std::function<void(int, int)> callback)
{
    impl_->mouseHandler->registerMoveCallback(callback);
}

void InputProcessor::registerMouseWheelCallback(std::function<void(float, float)> callback)
{
    impl_->mouseHandler->registerWheelCallback(callback);
}

void InputProcessor::registerClickCallback(MouseButton button, std::function<void()> callback)
{
    impl_->mouseHandler->registerClickCallback(button, callback);
}