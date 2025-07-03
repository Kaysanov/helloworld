#include "HotkeyRegistry.h"
#include <tuple>

bool HotkeyRegistry::Hotkey::operator<(const Hotkey &other) const
{
    if (type != other.type)
        return type < other.type;
    if (type == KEYBOARD)
        return std::tie(input.key, modifiers) < std::tie(other.input.key, other.modifiers);
    return std::tie(input.mouse_button, modifiers) < std::tie(other.input.mouse_button, other.modifiers);
}

void HotkeyRegistry::register_key_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback)
{
    Hotkey hk{Hotkey::KEYBOARD, {.key = key}, normalize_modifiers(modifiers), callback};
    hotkeys.insert(hk);
}

void HotkeyRegistry::register_mouse_hotkey(Uint8 button, SDL_Keymod modifiers, Callback callback)
{
    Hotkey hk{Hotkey::MOUSE, {.mouse_button = button}, normalize_modifiers(modifiers), callback};
    hotkeys.insert(hk);
}

bool HotkeyRegistry::process_event(const SDL_Event *event, SDL_Keymod current_mods) const
{
    current_mods = normalize_modifiers(current_mods);
    bool handled = false;

    if (event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
    {
        for (auto it = hotkeys.rbegin(); it != hotkeys.rend(); ++it)
        {
            const auto &hk = *it;
            if (hk.type == Hotkey::KEYBOARD &&
                hk.input.key == event->key.key &&
                (current_mods & hk.modifiers) == hk.modifiers)
            {
                hk.callback();
                handled = true;
                break;
            }
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        for (auto it = hotkeys.rbegin(); it != hotkeys.rend(); ++it)
        {
            const auto &hk = *it;
            if (hk.type == Hotkey::MOUSE &&
                hk.input.mouse_button == event->button.button &&
                (current_mods & hk.modifiers) == hk.modifiers)
            {
                hk.callback();
                handled = true;
                break;
            }
        }
    }

    return handled;
}

SDL_Keymod HotkeyRegistry::normalize_modifiers(SDL_Keymod mods)
{
    SDL_Keymod normalized = SDL_KMOD_NONE;
    if (mods & (SDL_KMOD_CTRL | SDL_KMOD_LCTRL | SDL_KMOD_RCTRL))
        normalized |= SDL_KMOD_CTRL;
    if (mods & (SDL_KMOD_SHIFT | SDL_KMOD_LSHIFT | SDL_KMOD_RSHIFT))
        normalized |= SDL_KMOD_SHIFT;
    if (mods & (SDL_KMOD_ALT | SDL_KMOD_LALT | SDL_KMOD_RALT))
        normalized |= SDL_KMOD_ALT;
    if (mods & (SDL_KMOD_GUI | SDL_KMOD_LGUI | SDL_KMOD_RGUI))
        normalized |= SDL_KMOD_GUI;
    return normalized;
}