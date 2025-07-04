#include "SDLInputSystem.h"
#include <iostream>

SDLInputSystem::SDLInputSystem() {}

SDLInputSystem::~SDLInputSystem()
{
    shutdown();
}

bool SDLInputSystem::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void SDLInputSystem::shutdown()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void SDLInputSystem::pollEvents()
{
    events.clear();
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        InputEvent ie;

        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:
            ie.type = InputEvent::KeyPressed;
            ie.data.key.key = convertSDLKey(event.key.key);
            ie.data.key.modifiers = convertSDLModifiers(SDL_GetModState());
            events.push_back(ie);
            break;

        case SDL_EVENT_KEY_UP:
            ie.type = InputEvent::KeyReleased;
            ie.data.key.key = convertSDLKey(event.key.key);
            ie.data.key.modifiers = convertSDLModifiers(SDL_GetModState());
            events.push_back(ie);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            ie.type = InputEvent::MouseButtonPressed;
            ie.data.mouseButton.button = convertSDLMouseButton(event.button.button);
            ie.data.mouseButton.modifiers = convertSDLModifiers(SDL_GetModState());
            events.push_back(ie);
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            ie.type = InputEvent::MouseButtonReleased;
            ie.data.mouseButton.button = convertSDLMouseButton(event.button.button);
            ie.data.mouseButton.modifiers = convertSDLModifiers(SDL_GetModState());
            events.push_back(ie);
            break;

        case SDL_EVENT_MOUSE_MOTION:
            ie.type = InputEvent::MouseMoved;
            ie.data.mouseMove.x = event.motion.x;
            ie.data.mouseMove.y = event.motion.y;
            events.push_back(ie);
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            ie.type = InputEvent::MouseWheel;
            ie.data.mouseWheel.x = event.wheel.x;
            ie.data.mouseWheel.y = event.wheel.y;
            events.push_back(ie);
            break;

        /*case SDL_EVENT_QUIT:
            ie.type = InputEvent::KeyPressed;
            ie.data.key.key = Key::Escape; // Эмулируем нажатие Escape для выхода
            events.push_back(ie);
            break;*/
        }
    }
}

const std::vector<InputEvent> &SDLInputSystem::getEvents() const
{
    return events;
}

bool SDLInputSystem::isKeyPressed(Key key) const
{
    const SDL_Scancode scancode = SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(key), NULL);
    const bool *state = SDL_GetKeyboardState(nullptr);
    return state[scancode];
}

bool SDLInputSystem::isMouseButtonPressed(MouseButton button) const
{
    Uint32 state = SDL_GetMouseState(nullptr, nullptr);
    switch (button)
    {
    case MouseButton::Left:
        return state & SDL_BUTTON_LMASK;
    case MouseButton::Right:
        return state & SDL_BUTTON_RMASK;
    case MouseButton::Middle:
        return state & SDL_BUTTON_MMASK;
    default:
        return false;
    }
}

MousePosition SDLInputSystem::getMousePosition() const
{
    float x, y;
    SDL_GetMouseState(&x, &y);
    return {static_cast<int>(x), static_cast<int>(y)};
}

void *SDLInputSystem::createWindow(const char *title, int width, int height)
{
    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);
    return window;
}

void SDLInputSystem::destroyWindow(void *window)
{
    if (this->window)
    {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

Key SDLInputSystem::convertSDLKey(SDL_Keycode sdlKey) const
{
    switch (sdlKey)
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
    case SDLK_RETURN:
        return Key::Enter;
    case SDLK_SPACE:
        return Key::Space;
    case SDLK_TAB:
        return Key::Tab;
    case SDLK_BACKSPACE:
        return Key::Backspace;
    case SDLK_DELETE:
        return Key::Delete;
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
    case SDLK_LEFT:
        return Key::Left;
    case SDLK_RIGHT:
        return Key::Right;
    case SDLK_UP:
        return Key::Up;
    case SDLK_DOWN:
        return Key::Down;
    default:
        return Key::Unknown;
    }
}

MouseButton SDLInputSystem::convertSDLMouseButton(Uint8 button) const
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
        return MouseButton::Left;
    }
}

uint16_t SDLInputSystem::convertSDLModifiers(SDL_Keymod mods) const
{
    uint16_t result = Modifier::None;
    if (mods & SDL_KMOD_LCTRL)       result |= Modifier::LeftCtrl;
    if (mods & SDL_KMOD_RCTRL)       result |= Modifier::RightCtrl;
    if (mods & SDL_KMOD_LSHIFT)      result |= Modifier::LeftShift;
    if (mods & SDL_KMOD_RSHIFT)      result |= Modifier::RightShift;
    if (mods & SDL_KMOD_LALT)        result |= Modifier::LeftAlt;
    if (mods & SDL_KMOD_RALT)        result |= Modifier::RightAlt;
    if (mods & SDL_KMOD_LGUI)        result |= Modifier::LeftSuper;
    if (mods & SDL_KMOD_RGUI)        result |= Modifier::RightSuper;
    return result;
}
