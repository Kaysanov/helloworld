#include "HotkeyRegistry.h"

void HotkeyRegistry::registerKeyboardHotkey(Key key, uint16_t modifiers, std::function<void()> callback) {
    Hotkey hk;
    hk.type = HotkeyType::Keyboard;
    hk.modifiers = modifiers;
    hk.input.key = key;
    callbacks_[hk] = callback;
}

void HotkeyRegistry::registerMouseHotkey(MouseButton button, uint16_t modifiers, std::function<void()> callback) {
    Hotkey hk;
    hk.type = HotkeyType::Mouse;
    hk.modifiers = modifiers;
    hk.input.button = button;
    callbacks_[hk] = callback;
}

std::function<void()> HotkeyRegistry::findCallback(const Hotkey& hk) const {
    if (auto it = callbacks_.find(hk); it != callbacks_.end()) {
        return it->second;
    }
    return nullptr;
}