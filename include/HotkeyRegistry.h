#ifndef HOTKEYREGISTRY_H
#define HOTKEYREGISTRY_H

#include <SDL3/SDL.h>
#include <functional>
#include <set>
#include <vector>
#include <unordered_map>

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
            Uint8 mouseButton;
        } input;
        SDL_Keymod modifiers;
        Callback callback;

        bool operator<(const Hotkey &other) const;
    };

    void registerKeyboardHotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback);
    void registerMouseHotkey(Uint8 mouseButton, SDL_Keymod modifiers, Callback callback);
    void registerClickCallback(Uint8 button, Callback callback);

    void checkHotkeys(const class InputState &inputState) const;
    void handleClick(Uint8 button) const;

private:
    std::set<Hotkey> hotkeys;
    std::unordered_map<Uint8, Callback> clickCallbacks;
};

#endif // HOTKEYREGISTRY_H