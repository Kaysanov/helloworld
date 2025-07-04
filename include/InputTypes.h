#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

// Коды клавиш (кроссплатформенные)
enum class Key : uint16_t
{
    Unknown = 0,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Escape,
    Enter,
    Space,
    Tab,
    Backspace,
    Delete,
    LeftCtrl,
    RightCtrl,
    LeftShift,
    RightShift,
    LeftAlt,
    RightAlt,
    LeftSuper,
    RightSuper,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    Left,
    Right,
    Up,
    Down
};

// Коды кнопок мыши
enum class MouseButton : uint8_t
{
    Left = 0,
    Right,
    Middle,
    Extra1,
    Extra2
};

// Модификаторы с разделением на левые/правые
enum Modifier : uint16_t
{
    None = 0,
    LeftCtrl = 1 << 0,
    RightCtrl = 1 << 1,
    LeftShift = 1 << 2,
    RightShift = 1 << 3,
    LeftAlt = 1 << 4,
    RightAlt = 1 << 5,
    LeftSuper = 1 << 6, // Windows/Command
    RightSuper = 1 << 7,

    // Комбинированные флаги для удобства
    Ctrl = LeftCtrl | RightCtrl,
    Shift = LeftShift | RightShift,
    Alt = LeftAlt | RightAlt,
    Super = LeftSuper | RightSuper
};

// Позиция мыши
struct MousePosition
{
    int x;
    int y;
};

// Универсальное событие
struct InputEvent
{
    enum Type
    {
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseWheel
    } type;

    union
    {
        struct
        {
            Key key;
            uint16_t modifiers; // Теперь используем 16-битные модификаторы
        } key;
        struct
        {
            MouseButton button;
            uint16_t modifiers;
        } mouseButton;
        struct
        {
            int x;
            int y;
        } mouseMove;
        struct
        {
            float x;
            float y;
        } mouseWheel;
    } data;
};

// Callback-типы
using ActionCallback = std::function<void()>;
using MouseMoveCallback = std::function<void(int, int)>;
using MouseWheelCallback = std::function<void(float, float)>;

// Вспомогательные функции
inline bool isCtrlPressed(uint16_t modifiers)
{
    return modifiers & (LeftCtrl | RightCtrl);
}

inline bool isLeftCtrlPressed(uint16_t modifiers)
{
    return modifiers & LeftCtrl;
}

inline bool isRightCtrlPressed(uint16_t modifiers)
{
    return modifiers & RightCtrl;
}

inline bool isShiftPressed(uint16_t modifiers)
{
    return modifiers & (LeftShift | RightShift);
}

inline bool isAltPressed(uint16_t modifiers)
{
    return modifiers & (LeftAlt | RightAlt);
}

inline bool isSuperPressed(uint16_t modifiers)
{
    return modifiers & (LeftSuper | RightSuper);
}