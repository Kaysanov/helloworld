#include "HotkeyManager.h"

void HotkeyManager::register_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback)
{
    hotkey_registry.register_key_hotkey(key, modifiers, callback);
}

void HotkeyManager::register_mouse_hotkey(Uint8 button, SDL_Keymod modifiers, Callback callback)
{
    hotkey_registry.register_mouse_hotkey(button, modifiers, callback);
}

void HotkeyManager::register_motion_callback(PositionCallback callback)
{
    mouse_processor.register_motion_callback(callback);
}

void HotkeyManager::register_wheel_callback(WheelCallback callback)
{
    mouse_processor.register_wheel_callback(callback);
}

void HotkeyManager::register_click_callback(Uint8 button, Callback callback)
{
    mouse_processor.register_click_callback(button, callback);
}

void HotkeyManager::update()
{
    InputState::get_instance().update();
}

void HotkeyManager::handle_event(const SDL_Event *event)
{
    InputState::get_instance().handle_event(event);
    mouse_processor.process_event(event);

    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        hotkey_registry.process_event(event, get_current_modifiers());
    }
}

bool HotkeyManager::is_key_pressed(SDL_Keycode key)
{
    return InputState::get_instance().is_key_pressed(key);
}

bool HotkeyManager::is_mouse_button_pressed(Uint8 button)
{
    return InputState::get_instance().is_mouse_button_pressed(button);
}

std::pair<int, int> HotkeyManager::get_mouse_position()
{
    return InputState::get_instance().get_mouse_position();
}

SDL_Keymod HotkeyManager::get_current_modifiers()
{
    return SDL_GetModState();
}