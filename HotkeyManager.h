#ifndef HOTKEYMANAGER_H
#define HOTKEYMANAGER_H

#include <SDL3/SDL.h>
#include <functional>
#include <set>
#include <vector>
#include <unordered_map>

class HotkeyManager
{
public:
    using Callback = std::function<void()>;
    using MousePositionCallback = std::function<void(int, int)>;
    using MouseWheelCallback = std::function<void(float, float)>;

    // Регистрация горячих клавиш
    void register_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback);
    void register_mouse_hotkey(Uint8 mouse_button, SDL_Keymod modifiers, Callback callback);

    // Регистрация обработчиков мыши
    void register_motion_callback(MousePositionCallback callback);
    void register_wheel_callback(MouseWheelCallback callback);
    void register_click_callback(Uint8 button, Callback callback);

    // Обновление состояния
    void update();

    // Обработка событий
    void handle_event(const SDL_Event *event);

    // Получение состояния
    static bool is_key_pressed(SDL_Keycode key);
    static bool is_mouse_button_pressed(Uint8 button);
    static std::pair<int, int> get_mouse_position();

private:
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

        bool operator<(const Hotkey &other) const
        {
            if (type != other.type)
                return type < other.type;
            if (type == KEYBOARD)
                return std::tie(input.key, modifiers) < std::tie(other.input.key, other.modifiers);
            return std::tie(input.mouse_button, modifiers) < std::tie(other.input.mouse_button, other.modifiers);
        }
    };

    // Кэш преобразования Keycode -> Scancode
    std::unordered_map<SDL_Keycode, SDL_Scancode> keycode_to_scancode;

    // Коллекции обработчиков
    std::set<Hotkey> hotkeys;
    std::unordered_map<Uint8, Callback> click_callbacks;
    MousePositionCallback motion_callback = nullptr;
    MouseWheelCallback wheel_callback = nullptr;

    // Состояние мыши
    static int mouse_x;
    static int mouse_y;
    static Uint32 mouse_buttons;
    static float wheel_x;
    static float wheel_y;

    // Вспомогательные функции
    SDL_Scancode get_scancode(SDL_Keycode key);
    static SDL_Keymod normalize_modifiers(SDL_Keymod mods);
    static SDL_Keymod get_current_modifiers();

    // Преобразование номера кнопки в битовую маску
    static Uint32 button_to_mask(Uint8 button);
};

#endif // HOTKEYMANAGER_H