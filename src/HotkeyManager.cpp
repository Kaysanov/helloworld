#include "HotkeyManager.h"

HotkeyManager::HotkeyManager()
{
    inputState.resetFrameState();
}

void HotkeyManager::registerKeyboardHotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback)
{
    hotkeyRegistry.registerKeyboardHotkey(key, modifiers, callback);
}

void HotkeyManager::registerMouseHotkey(Uint8 mouseButton, SDL_Keymod modifiers, Callback callback)
{
    hotkeyRegistry.registerMouseHotkey(mouseButton, modifiers, callback);
}

void HotkeyManager::registerClickCallback(Uint8 button, Callback callback)
{
    hotkeyRegistry.registerClickCallback(button, callback);
}

void HotkeyManager::registerMouseMoveCallback(MousePositionCallback callback)
{
    eventProcessor.setMouseMoveCallback(callback);
}

void HotkeyManager::registerMouseWheelCallback(MouseWheelCallback callback)
{
    eventProcessor.setMouseWheelCallback(callback);
}

void HotkeyManager::handleEvent(const SDL_Event *event)
{
    eventProcessor.processEvent(event, inputState, hotkeyRegistry);
}

void HotkeyManager::update()
{
    inputState.resetFrameState();
    hotkeyRegistry.checkHotkeys(inputState);
}