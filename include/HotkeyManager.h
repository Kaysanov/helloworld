#ifndef HOTKEYMANAGER_H
#define HOTKEYMANAGER_H

#include "InputState.h"
#include "HotkeyRegistry.h"
#include "EventProcessor.h"

class HotkeyManager
{
public:
    using Callback = HotkeyRegistry::Callback;
    using MousePositionCallback = EventProcessor::MousePositionCallback;
    using MouseWheelCallback = EventProcessor::MouseWheelCallback;

    HotkeyManager();

    void registerKeyboardHotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback);
    void registerMouseHotkey(Uint8 mouseButton, SDL_Keymod modifiers, Callback callback);
    void registerClickCallback(Uint8 button, Callback callback);
    void registerMouseMoveCallback(MousePositionCallback callback);
    void registerMouseWheelCallback(MouseWheelCallback callback);

    void handleEvent(const SDL_Event *event);
    void update();

private:
    InputState inputState;
    HotkeyRegistry hotkeyRegistry;
    EventProcessor eventProcessor;
};

#endif // HOTKEYMANAGER_H