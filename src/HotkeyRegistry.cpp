#include "HotkeyRegistry.h"
#include "InputState.h"
#include "ModifierUtils.h"

bool HotkeyRegistry::Hotkey::operator<(const Hotkey &other) const
{
    if (type != other.type)
        return type < other.type;
    if (type == KEYBOARD)
        return std::tie(input.key, modifiers) < std::tie(other.input.key, other.modifiers);
    return std::tie(input.mouseButton, modifiers) < std::tie(other.input.mouseButton, other.modifiers);
}

void HotkeyRegistry::registerKeyboardHotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback)
{
    Hotkey hk;
    hk.type = Hotkey::KEYBOARD;
    hk.input.key = key;
    hk.modifiers = ModifierUtils::normalize(modifiers);
    hk.callback = callback;
    hotkeys.insert(hk);
}

void HotkeyRegistry::registerMouseHotkey(Uint8 mouseButton, SDL_Keymod modifiers, Callback callback)
{
    Hotkey hk;
    hk.type = Hotkey::MOUSE;
    hk.input.mouseButton = mouseButton;
    hk.modifiers = ModifierUtils::normalize(modifiers);
    hk.callback = callback;
    hotkeys.insert(hk);
}

void HotkeyRegistry::registerClickCallback(Uint8 button, Callback callback)
{
    clickCallbacks[button] = callback;
}

void HotkeyRegistry::checkHotkeys(const InputState &inputState) const
{
    SDL_Keymod currentMods = ModifierUtils::normalize(SDL_GetModState());

    for (const auto &hk : hotkeys)
    {
        if (!ModifierUtils::checkModifiers(hk.modifiers, currentMods))
        {
            continue;
        }

        bool pressed = false;
        if (hk.type == Hotkey::KEYBOARD)
        {
            pressed = inputState.isKeyPressed(hk.input.key);
        }
        else
        {
            pressed = inputState.isMouseButtonPressed(hk.input.mouseButton);
        }

        if (pressed)
        {
            hk.callback();
        }
    }
}

void HotkeyRegistry::handleClick(Uint8 button) const
{
    if (auto it = clickCallbacks.find(button); it != clickCallbacks.end())
    {
        it->second();
    }
}