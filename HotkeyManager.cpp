#include "HotkeyManager.h"
#include <algorithm>
#include <fmt/core.h>

// Регистрация горячей клавиши
void HotkeyManager::register_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback)
{
    Hotkey hk;
    hk.key = key;
    hk.modifiers = normalize_modifiers(modifiers);
    hk.callback = callback;
    hotkeys.insert(hk);
}

// Регистрация комбинации клавиш
void HotkeyManager::register_combo(const std::vector<SDL_Keycode> &keys, Callback callback)
{
    KeyCombo combo;
    combo.keys = keys;
    std::sort(combo.keys.begin(), combo.keys.end());
    combo.callback = callback;
    combos.insert(combo);
}

// Обновление состояния
/*void HotkeyManager::update()
{
    const bool *keyboard_state = SDL_GetKeyboardState(nullptr);
    SDL_Keymod current_mods = get_current_modifiers();

    // Проверка горячих клавиш
    for (const auto &hk : hotkeys)
    {
        // Проверка модификаторов
        if (hk.modifiers != current_mods)
            continue;

        // Проверка клавиши
        SDL_Scancode scancode = SDL_GetScancodeFromKey(hk.key, &current_mods);
        if (keyboard_state[scancode])
        {
            if (active_hotkeys.find(hk) == active_hotkeys.end())
            {
                hk.callback();
                active_hotkeys.insert(hk);
            }
        }
        else
        {
            active_hotkeys.erase(hk);
        }
    }

    // Проверка комбинаций клавиш
    for (const auto &combo : combos)
    {
        bool all_pressed = true;

        for (SDL_Keycode key : combo.keys)
        {
            SDL_Scancode scancode = SDL_GetScancodeFromKey(key, &current_mods);
            if (!keyboard_state[scancode])
            {
                all_pressed = false;
                break;
            }
        }

        if (all_pressed)
        {
            if (active_combos.find(combo) == active_combos.end())
            {
                combo.callback();
                active_combos.insert(combo);
            }
        }
        else
        {
            active_combos.erase(combo);
        }
    }
}
*/
void HotkeyManager::update()
{
    const bool *keyboard_state = SDL_GetKeyboardState(nullptr);
    const SDL_Keymod current_mods = get_current_modifiers();



    // Проверка горячих клавиш
    for (const auto &hk : hotkeys)
    {
        // Проверка модификаторов
        if (hk.modifiers != current_mods)
            continue;
        
        fmt::print("{}, {}\n", *keyboard_state, current_mods);

        // Проверка клавиши
        if (is_key_pressed(hk.key, keyboard_state))
        {
            if (active_hotkeys.find(hk) == active_hotkeys.end())
            {
                hk.callback();
                active_hotkeys.insert(hk);
            }
        }
        else
        {
            active_hotkeys.erase(hk);
        }
    }

    // Проверка комбинаций клавиш
    for (const auto &combo : combos)
    {
        bool all_pressed = true;

        for (SDL_Keycode key : combo.keys)
        {
            if (!is_key_pressed(key, keyboard_state))
            {
                all_pressed = false;
                break;
            }
        }

        if (all_pressed)
        {
            if (active_combos.find(combo) == active_combos.end())
            {
                combo.callback();
                active_combos.insert(combo);
            }
        }
        else
        {
            active_combos.erase(combo);
        }
    }
}
bool HotkeyManager::is_key_pressed(SDL_Keycode key, const bool *keyboard_state)
{
    SDL_Keymod dummy_mod;
    const SDL_Scancode scancode = SDL_GetScancodeFromKey(key, &dummy_mod);
    return keyboard_state[scancode];
}
// Обработка событий
void HotkeyManager::handle_event(const SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_UP)
    {
        active_hotkeys.clear();
        active_combos.clear();
    }
}

// Проверка модификаторов
bool HotkeyManager::is_ctrl_pressed()
{
    return SDL_GetModState() & SDL_KMOD_CTRL;
}

bool HotkeyManager::is_shift_pressed()
{
    return SDL_GetModState() & SDL_KMOD_SHIFT;
}

bool HotkeyManager::is_alt_pressed()
{
    return SDL_GetModState() & SDL_KMOD_ALT;
}

bool HotkeyManager::is_gui_pressed()
{
    return SDL_GetModState() & SDL_KMOD_GUI;
}

// Вспомогательные функции
SDL_Keymod HotkeyManager::normalize_modifiers(SDL_Keymod mods)
{
    return mods & (SDL_KMOD_CTRL | SDL_KMOD_SHIFT | SDL_KMOD_ALT | SDL_KMOD_GUI);
}

SDL_Keymod HotkeyManager::get_current_modifiers()
{
    return normalize_modifiers(SDL_GetModState());
}