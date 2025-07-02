#include "HotkeyManager.h"
#include <algorithm>

// Инициализация статических переменных
int HotkeyManager::mouse_x = 0;
int HotkeyManager::mouse_y = 0;
Uint32 HotkeyManager::mouse_buttons = 0;
float HotkeyManager::wheel_x = 0;
float HotkeyManager::wheel_y = 0;

void HotkeyManager::register_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback)
{
    Hotkey hk;
    hk.type = Hotkey::KEYBOARD;
    hk.input.key = key;
    hk.modifiers = normalize_modifiers(modifiers);
    hk.callback = callback;
    hotkeys.insert(hk);

    // Кэшируем сканкод
    get_scancode(key);
}

void HotkeyManager::register_mouse_hotkey(Uint8 mouse_button, SDL_Keymod modifiers, Callback callback)
{
    Hotkey hk;
    hk.type = Hotkey::MOUSE;
    hk.input.mouse_button = mouse_button;
    hk.modifiers = normalize_modifiers(modifiers);
    hk.callback = callback;
    hotkeys.insert(hk);
}

void HotkeyManager::register_click_callback(Uint8 button, Callback callback)
{
    click_callbacks[button] = callback;
}

void HotkeyManager::register_motion_callback(MousePositionCallback callback)
{
    motion_callback = callback;
}

void HotkeyManager::register_wheel_callback(MouseWheelCallback callback)
{
    wheel_callback = callback;
}

void HotkeyManager::update()
{
    // Обновляем состояние колесика
    wheel_x = 0;
    wheel_y = 0;
}

void HotkeyManager::handle_event(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        mouse_x = event->motion.x;
        mouse_y = event->motion.y;
        if (motion_callback)
        {
            motion_callback(mouse_x, mouse_y);
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        mouse_buttons |= button_to_mask(event->button.button);
        if (click_callbacks.find(event->button.button) != click_callbacks.end())
        {
            click_callbacks[event->button.button]();
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        mouse_buttons &= ~button_to_mask(event->button.button);
        break;

    case SDL_EVENT_MOUSE_WHEEL:
        wheel_x = event->wheel.x;
        wheel_y = event->wheel.y;
        if (wheel_callback)
        {
            wheel_callback(wheel_x, wheel_y);
        }
        break;
    }

    // Проверка горячих клавиш
    const SDL_Keymod current_mods = get_current_modifiers();
    const bool *keyboard_state = SDL_GetKeyboardState(nullptr);

    for (const auto &hk : hotkeys)
    {
        // Проверка модификаторов
        if (hk.modifiers != current_mods)
            continue;

        // Проверка основного действия
        bool pressed = false;
        if (hk.type == Hotkey::KEYBOARD)
        {
            SDL_Scancode scancode = get_scancode(hk.input.key);
            pressed = keyboard_state[scancode];
        }
        else
        {
            pressed = (mouse_buttons & button_to_mask(hk.input.mouse_button)) != 0;
        }

        if (pressed)
        {
            hk.callback();
            // Предотвращаем многократное срабатывание
            break;
        }
    }
}

SDL_Scancode HotkeyManager::get_scancode(SDL_Keycode key)
{
    auto it = keycode_to_scancode.find(key);
    if (it != keycode_to_scancode.end())
    {
        return it->second;
    }

    SDL_Keymod dummy;
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, &dummy);
    keycode_to_scancode[key] = scancode;
    return scancode;
}

bool HotkeyManager::is_key_pressed(SDL_Keycode key)
{
    SDL_Keymod dummy;
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, &dummy);
    const bool *state = SDL_GetKeyboardState(nullptr);
    return state[scancode];
}

bool HotkeyManager::is_mouse_button_pressed(Uint8 button)
{
    return (mouse_buttons & button_to_mask(button)) != 0;
}

std::pair<int, int> HotkeyManager::get_mouse_position()
{
    return {mouse_x, mouse_y};
}

Uint32 HotkeyManager::button_to_mask(Uint8 button)
{
    // SDL_BUTTON_LEFT -> SDL_BUTTON_LMASK и т.д.
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return SDL_BUTTON_LMASK;
    case SDL_BUTTON_MIDDLE:
        return SDL_BUTTON_MMASK;
    case SDL_BUTTON_RIGHT:
        return SDL_BUTTON_RMASK;
    case SDL_BUTTON_X1:
        return SDL_BUTTON_X1MASK;
    case SDL_BUTTON_X2:
        return SDL_BUTTON_X2MASK;
    default:
        return 0;
    }
}

SDL_Keymod HotkeyManager::normalize_modifiers(SDL_Keymod mods)
{
    return mods & (SDL_KMOD_CTRL | SDL_KMOD_SHIFT | SDL_KMOD_ALT | SDL_KMOD_GUI);
}

SDL_Keymod HotkeyManager::get_current_modifiers()
{
    return normalize_modifiers(SDL_GetModState());
}