#ifndef HOTKEYMANAGER_H
#define HOTKEYMANAGER_H

#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>
#include <set>
#include <vector>

class HotkeyManager {
public:
    using Callback = std::function<void()>;

    // Регистрация горячей клавиши (клавиша + модификаторы)
    void register_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback);
    
    // Регистрация комбинации клавиш (без модификаторов)
    void register_combo(const std::vector<SDL_Keycode>& keys, Callback callback);
    
    // Обновление состояния горячих клавиш
    void update();
    
    // Обработка событий SDL
    void handle_event(const SDL_Event* event);
    
    // Проверка активности модификаторов
    static bool is_ctrl_pressed();
    static bool is_shift_pressed();
    static bool is_alt_pressed();
    static bool is_gui_pressed();

private:
    struct Hotkey {
        SDL_Keycode key;
        SDL_Keymod modifiers;
        Callback callback;
        
        bool operator<(const Hotkey& other) const {
            return std::tie(key, modifiers) < std::tie(other.key, other.modifiers);
        }
    };
    
    struct KeyCombo {
        std::vector<SDL_Keycode> keys;
        Callback callback;
        
        bool operator<(const KeyCombo& other) const {
            return keys < other.keys;
        }
    };
    
    std::set<Hotkey> hotkeys;
    std::set<KeyCombo> combos;
    std::set<Hotkey> active_hotkeys;
    std::set<KeyCombo> active_combos;
    
    // Нормализация модификаторов
    static SDL_Keymod normalize_modifiers(SDL_Keymod mods);
    
    // Получение текущих модификаторов
    static SDL_Keymod get_current_modifiers();
    
    // Проверка активности клавиши
    static bool is_key_pressed(SDL_Keycode key, const bool* keyboard_state);
};



#endif // HOTKEYMANAGER_H