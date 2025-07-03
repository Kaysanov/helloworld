#ifndef HOTKEYREGISTRY_H
#define HOTKEYREGISTRY_H

#include <SDL3/SDL.h>
#include <functional>
#include <set>

class HotkeyRegistry
{
public:
    using Callback = std::function<void()>;

    struct Hotkey
    {
        enum Type
        {
            KEYBOARD,
            MOUSE
        } type;
        union
        {
            SDL_Keycode key;
            Uint8 mouse_button;
        } input;
        SDL_Keymod modifiers;
        Callback callback;

        bool operator<(const Hotkey &other) const;
    };

    void register_key_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback);
    void register_mouse_hotkey(Uint8 button, SDL_Keymod modifiers, Callback callback);
    bool process_event(const SDL_Event *event, SDL_Keymod current_mods) const;

private:
    static SDL_Keymod normalize_modifiers(SDL_Keymod mods);

    std::set<Hotkey> hotkeys;
};

#endif