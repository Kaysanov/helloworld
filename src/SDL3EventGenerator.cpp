#include "SDL3EventGenerator.h"
#include "InputProcessor.h"
#include <iostream>
#include "InputTypes.h"
#include <fmt/core.h>

InputEvent SDL3EventGenerator::convertSDLEvent(const SDL_Event &e) const
{
    InputEvent event = {};

    switch (e.type)
    {
    case SDL_EVENT_KEY_DOWN:
        event.type = InputEventType::KeyPressed;
        event.data.key.key = convertSDLKey(e.key.key);
        event.data.key.modifiers = convertSDLModifiers(e.key.mod);
        break;

    case SDL_EVENT_KEY_UP:
        event.type = InputEventType::KeyReleased;
        event.data.key.key = convertSDLKey(e.key.key);
        event.data.key.modifiers = convertSDLModifiers(e.key.mod);
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        event.type = InputEventType::MouseButtonPressed;
        event.data.mouseButton.button = convertSDLMouseButton(e.button.button);
        event.data.mouseButton.modifiers = convertSDLModifiers(SDL_GetModState());
        event.data.mouseButton.x = e.button.x;
        event.data.mouseButton.y = e.button.y;
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        event.type = InputEventType::MouseButtonReleased;
        event.data.mouseButton.button = convertSDLMouseButton(e.button.button);
        event.data.mouseButton.modifiers = convertSDLModifiers(SDL_GetModState());
        event.data.mouseButton.x = e.button.x;
        event.data.mouseButton.y = e.button.y;
        break;

    case SDL_EVENT_MOUSE_MOTION:
        event.type = InputEventType::MouseMoved;
        event.data.mouseMove.x = e.motion.x;
        event.data.mouseMove.y = e.motion.y;
        break;

    case SDL_EVENT_MOUSE_WHEEL:
        event.type = InputEventType::MouseWheel;
        event.data.mouseWheel.x = e.wheel.x;
        event.data.mouseWheel.y = e.wheel.y;
        break;

    default:
        event.type = InputEventType::Unknown;
    }

    return event;
}

Key SDL3EventGenerator::convertSDLKey(SDL_Keycode key) const
{
    switch (key)
    {
    case SDLK_A:
        return Key::A;
    case SDLK_B:
        return Key::B;
    case SDLK_C:
        return Key::C;
    case SDLK_D:
        return Key::D;
    case SDLK_E:
        return Key::E;
    case SDLK_F:
        return Key::F;
    case SDLK_G:
        return Key::G;
    case SDLK_H:
        return Key::H;
    case SDLK_I:
        return Key::I;
    case SDLK_J:
        return Key::J;
    case SDLK_K:
        return Key::K;
    case SDLK_L:
        return Key::L;
    case SDLK_M:
        return Key::M;
    case SDLK_N:
        return Key::N;
    case SDLK_O:
        return Key::O;
    case SDLK_P:
        return Key::P;
    case SDLK_Q:
        return Key::Q;
    case SDLK_R:
        return Key::R;
    case SDLK_S:
        return Key::S;
    case SDLK_T:
        return Key::T;
    case SDLK_U:
        return Key::U;
    case SDLK_V:
        return Key::V;
    case SDLK_W:
        return Key::W;
    case SDLK_X:
        return Key::X;
    case SDLK_Y:
        return Key::Y;
    case SDLK_Z:
        return Key::Z;
    case SDLK_0:
        return Key::Num0;
    case SDLK_1:
        return Key::Num1;
    case SDLK_2:
        return Key::Num2;
    case SDLK_3:
        return Key::Num3;
    case SDLK_4:
        return Key::Num4;
    case SDLK_5:
        return Key::Num5;
    case SDLK_6:
        return Key::Num6;
    case SDLK_7:
        return Key::Num7;
    case SDLK_8:
        return Key::Num8;
    case SDLK_9:
        return Key::Num9;
    case SDLK_ESCAPE:
        return Key::Escape;
    case SDLK_SPACE:
        return Key::Space;
    case SDLK_RETURN:
        return Key::Enter;
    case SDLK_TAB:
        return Key::Tab;
    case SDLK_LEFT:
        return Key::Left;
    case SDLK_RIGHT:
        return Key::Right;
    case SDLK_UP:
        return Key::Up;
    case SDLK_DOWN:
        return Key::Down;
    case SDLK_F1:
        return Key::F1;
    case SDLK_F2:
        return Key::F2;
    case SDLK_F3:
        return Key::F3;
    case SDLK_F4:
        return Key::F4;
    case SDLK_F5:
        return Key::F5;
    case SDLK_F6:
        return Key::F6;
    case SDLK_F7:
        return Key::F7;
    case SDLK_F8:
        return Key::F8;
    case SDLK_F9:
        return Key::F9;
    case SDLK_F10:
        return Key::F10;
    case SDLK_F11:
        return Key::F11;
    case SDLK_F12:
        return Key::F12;
    case SDLK_PAUSE:
        return Key::Pause;
    case SDLK_INSERT:
        return Key::Insert;
    case SDLK_HOME:
        return Key::Home;
    case SDLK_DELETE:
        return Key::Delete;
    case SDLK_END:
        return Key::End;
    case SDLK_BACKSPACE:
        return Key::Backspace;
    case SDLK_KP_0:
        return Key::Numpad0;
    case SDLK_KP_1:
        return Key::Numpad1;
    case SDLK_KP_2:
        return Key::Numpad2;
    case SDLK_KP_3:
        return Key::Numpad3;
    case SDLK_KP_4:
        return Key::Numpad4;
    case SDLK_KP_5:
        return Key::Numpad5;
    case SDLK_KP_6:
        return Key::Numpad6;
    case SDLK_KP_7:
        return Key::Numpad7;
    case SDLK_KP_8:
        return Key::Numpad8;
    case SDLK_KP_9:
        return Key::Numpad9;
    case SDLK_KP_DIVIDE:
        return Key::Divide;
    case SDLK_KP_MULTIPLY:
        return Key::Multiply;
    case SDLK_KP_MINUS:
        return Key::Subtract;
    case SDLK_KP_PLUS:
        return Key::Add;
    case SDLK_KP_ENTER:
        return Key::Enter;
    case SDLK_KP_PERIOD:
        return Key::Decimal;
    case SDLK_LCTRL:
        return Key::LeftCtrl;
    case SDLK_RCTRL:
        return Key::RightCtrl;
    case SDLK_LSHIFT:
        return Key::LeftShift;
    case SDLK_RSHIFT:
        return Key::RightShift;
    case SDLK_LALT:
        return Key::LeftAlt;
    case SDLK_RALT:
        return Key::RightAlt;
    case SDLK_LGUI:
        return Key::LeftSuper;
    case SDLK_RGUI:
        return Key::RightSuper;
    case SDLK_MENU:
        return Key::Menu;
    case SDLK_APPLICATION:
        return Key::Application;
    default:
        return Key::Unknown;
    }
}

MouseButton SDL3EventGenerator::convertSDLMouseButton(Uint32 button) const
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return MouseButton::Left;
    case SDL_BUTTON_RIGHT:
        return MouseButton::Right;
    case SDL_BUTTON_MIDDLE:
        return MouseButton::Middle;
    case SDL_BUTTON_X1:
        return MouseButton::Extra1;
    case SDL_BUTTON_X2:
        return MouseButton::Extra2;
    default:
        return MouseButton::None;
    }
}

uint16_t SDL3EventGenerator::convertSDLModifiers(Uint32 mod) const
{
    uint16_t modifiers = Modifier::None;
    if (mod & SDL_KMOD_LCTRL)
        modifiers |= Modifier::LeftCtrl;
    if (mod & SDL_KMOD_RCTRL)
        modifiers |= Modifier::RightCtrl;
    if (mod & SDL_KMOD_SHIFT)
        modifiers |= Modifier::LeftShift;
    if (mod & SDL_KMOD_RSHIFT)
        modifiers |= Modifier::RightShift;
    if (mod & SDL_KMOD_ALT)
        modifiers |= Modifier::LeftAlt;
    if (mod & SDL_KMOD_RALT)
        modifiers |= Modifier::RightAlt;
    if (mod & SDL_KMOD_GUI)
        modifiers |= Modifier::LeftSuper;
    if (mod & SDL_KMOD_RGUI)
        modifiers |= Modifier::RightSuper;
    return modifiers;
}

void SDL3EventGenerator::runEventLoop(InputProcessor &processor)
{
    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }

            InputEvent event = convertSDLEvent(e);

            if (event.type != InputEventType::Unknown)
            {
                processor.handleEvent(event);
            }
        }

        // Отрисовка и другая логика
        SDL_Delay(16);
    }
}