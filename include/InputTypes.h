#pragma once
#include <cstddef> // Для size_t
#include <cstdint>
#include <string>
#include <key.h>
#include <mousebutton.h>

// Общие типы данных для системы ввода
/*
enum class Key
{
    Unknown,
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
    Space,
    Enter,
    Tab,
    Left,
    Right,
    Up,
    Down,
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
    PrintScreen,
    ScrollLock,
    Pause,
    Insert,
    Home,
    PageUp,
    Delete,
    End,
    PageDown,
    Backspace,
    CapsLock,
    NumLock,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    Divide,
    Multiply,
    Subtract,
    Add,
    Decimal,
    LeftCtrl,
    RightCtrl,
    LeftShift,
    RightShift,
    LeftAlt,
    RightAlt,
    LeftSuper,
    RightSuper,
    Menu,
    Application
};

enum class MouseButton
{
    None,
    Left,
    Right,
    Middle,
    Extra1,
    Extra2
};

static MouseButton FromString(const std::string &str)
{
    if (str == "Left")
        return MouseButton::Left;
    else if (str == "Right")
        return MouseButton::Right;
    else if (str == "Middle")
        return MouseButton::Middle;
    else if (str == "Extra1")
        return MouseButton::Extra1;
    else if (str == "Extra2")
        return MouseButton::Extra2;
    else
        return MouseButton::None;
}*/

enum class HotkeyType
{
    Keyboard,
    Mouse,
    Gamepad,
    Custom
};

enum InputEventType
{
    Unknown,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseWheel,
    GamepadButtonPressed
};

namespace Modifier
{
    constexpr uint16_t None = 0x0000;
    constexpr uint16_t LeftCtrl = 0x0001;
    constexpr uint16_t RightCtrl = 0x0002;
    constexpr uint16_t LeftShift = 0x0004;
    constexpr uint16_t RightShift = 0x0008;
    constexpr uint16_t LeftAlt = 0x0010;
    constexpr uint16_t RightAlt = 0x0020;
    constexpr uint16_t LeftSuper = 0x0040;
    constexpr uint16_t RightSuper = 0x0080;

    constexpr uint16_t Ctrl = LeftCtrl | RightCtrl;
    constexpr uint16_t Shift = LeftShift | RightShift;
    constexpr uint16_t Alt = LeftAlt | RightAlt;
    constexpr uint16_t Super = LeftSuper | RightSuper;
}

struct KeyEvent
{
    Key key;
    uint16_t modifiers;
};

struct MouseButtonEvent
{
    MouseButton button;
    uint16_t modifiers;
    int x, y;
};

struct MouseMoveEvent
{
    int x, y;
};

struct MouseWheelEvent
{
    float x, y;
};

union InputEventData
{
    KeyEvent key;
    MouseButtonEvent mouseButton;
    MouseMoveEvent mouseMove;
    MouseWheelEvent mouseWheel;
};

struct InputEvent
{
    InputEventType type;
    InputEventData data;
};


/*
enum class InputState {
    Default,
    EditMode,
    CombatMode,
    DialogMode,
    CustomState1,
    CustomState2,
    // Можно расширять по необходимости
    _Count // Для определения количества состояний
};

constexpr size_t INPUT_STATE_COUNT = static_cast<size_t>(InputState::_Count);
*/