#include "HotkeyRegistry.h"
#include <fmt/core.h>
#include "ConfigManager.h"



void HotkeyRegistry::registerMouseHotkey(InputState state, MouseButton button, uint16_t modifiers, std::function<void()> callback)
{
    Hotkey hk;
    hk.type = HotkeyType::Mouse;
    hk.modifiers = modifiers;
    hk.input.button = button;
    size_t stateIndex = static_cast<size_t>(state);
    stateCallbacks_[stateIndex][hk] = callback;
}
void HotkeyRegistry::registerMouseRelease(InputState state,MouseButton button, uint16_t modifiers, std::function<void()> callback)
{
    Hotkey hk;
    hk.type = HotkeyType::Mouse;
    hk.modifiers = modifiers;
    hk.input.button = button;
    size_t stateIndex = static_cast<size_t>(state);
    stateReleaseCallbacks_[stateIndex][hk] = callback;
}

void HotkeyRegistry::registerKeyboardHotkey(InputState state, Key key, uint16_t modifiers, std::function<void()> callback) {
    Hotkey hk;
    hk.type = HotkeyType::Keyboard;
    hk.modifiers = modifiers;
    hk.input.key = key;
    
    size_t stateIndex = static_cast<size_t>(state);
    stateCallbacks_[stateIndex][hk] = callback;
}

void HotkeyRegistry::registerKeyboardRelease(InputState state, Key key, uint16_t modifiers, std::function<void()> callback) {
    Hotkey hk;
    hk.type = HotkeyType::Keyboard;
    hk.modifiers = modifiers;
    hk.input.key = key;
    
    size_t stateIndex = static_cast<size_t>(state);
    stateReleaseCallbacks_[stateIndex][hk] = callback;
}



std::function<void()> HotkeyRegistry::findCallback(InputState state, const Hotkey& hk) const {
    size_t stateIndex = static_cast<size_t>(state);
    if (auto it = stateCallbacks_[stateIndex].find(hk); it != stateCallbacks_[stateIndex].end()) {
        return it->second;
    }
    return nullptr;
}

std::function<void()> HotkeyRegistry::findReleaseCallback(InputState state, const Hotkey& hk) const {
    size_t stateIndex = static_cast<size_t>(state);
    if (auto it = stateReleaseCallbacks_[stateIndex].find(hk); it != stateReleaseCallbacks_[stateIndex].end()) {
        return it->second;
    }
    return nullptr;
}

void HotkeyRegistry::setKeyState(Key key, bool state)
{
    keyStates_[key] = state;
}

bool HotkeyRegistry::isKeyDown(Key key) const
{
    if (auto it = keyStates_.find(key); it != keyStates_.end())
    {
        return it->second;
    }
    return false;
}

void HotkeyRegistry::setMouseButtonState(MouseButton button, bool state)
{
    mouseButtonStates_[button] = state;
}

bool HotkeyRegistry::isMouseButtonDown(MouseButton button) const
{
    if (auto it = mouseButtonStates_.find(button); it != mouseButtonStates_.end())
    {
        return it->second;
    }
    return false;
}