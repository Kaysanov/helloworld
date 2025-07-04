#pragma once
#include "InputTypes.h"
#include <map>
#include <vector>
#include <functional>
#include <type_traits>

class HotkeyManager {
public:
    // Типы горячих клавиш
    enum class HotkeyType {
        Keyboard,  // Клавиатурная комбинация
        Mouse,     // Комбинация с кнопкой мыши
        Gamepad,   // Для будущего расширения
        Custom     // Специальные обработчики
    };
    
    // Структура горячей клавиши
    struct Hotkey {
        HotkeyType type;
        union {
            Key key;             // Для клавиатуры
            MouseButton button;  // Для мыши
            int gamepadButton;   // Для геймпада
        } input;
        uint16_t modifiers;
        
        bool operator<(const Hotkey& other) const;
    };
    
    // Шаблонная функция для регистрации горячих клавиш
    template <typename T>
    void registerHotkey(T input, uint16_t modifiers, std::function<void()> callback) {
        if constexpr (std::is_same_v<T, Key>) {
            Hotkey hk{HotkeyType::Keyboard, {.key = input}, modifiers};
            hotkeyCallbacks[hk] = callback;
        }
        else if constexpr (std::is_same_v<T, MouseButton>) {
            Hotkey hk{HotkeyType::Mouse, {.button = input}, modifiers};
            hotkeyCallbacks[hk] = callback;
        }
        else {
            static_assert(std::is_same_v<T, void>, "Unsupported input type");
        }
    }
    
    // Регистрация обработчиков мыши
    void registerMouseMoveCallback(std::function<void(int, int)> callback);
    void registerMouseWheelCallback(std::function<void(float, float)> callback);
    void registerClickCallback(MouseButton button, std::function<void()> callback);
    
    // Обработка событий
    void processEvents(const std::vector<InputEvent>& events);
    
    // Обновление состояния
    void update();

private:
    // Основной контейнер для хранения колбэков
    std::map<Hotkey, std::function<void()>> hotkeyCallbacks;
    
    // Контейнеры для обработчиков мыши
    std::map<MouseButton, std::function<void()>> clickCallbacks;
    std::function<void(int, int)> mouseMoveCallback = nullptr;
    std::function<void(float, float)> mouseWheelCallback = nullptr;
    
    // Функции сравнения
    bool matchesKeyboardHotkey(const Hotkey& hk, const InputEvent& event) const;
    bool matchesMouseHotkey(const Hotkey& hk, const InputEvent& event) const;
};

// Реализация inline методов
inline void HotkeyManager::registerMouseMoveCallback(std::function<void(int, int)> callback) {
    mouseMoveCallback = callback;
}

inline void HotkeyManager::registerMouseWheelCallback(std::function<void(float, float)> callback) {
    mouseWheelCallback = callback;
}

inline void HotkeyManager::registerClickCallback(MouseButton button, std::function<void()> callback) {
    clickCallbacks[button] = callback;
}

inline void HotkeyManager::update() {
    // Можно добавить логику обработки состояний
}