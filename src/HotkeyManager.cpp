#include "HotkeyManager.h"
#include <iostream>
#include <tuple>

using namespace std;

bool HotkeyManager::Hotkey::operator<(const Hotkey &other) const
{
    if (type != other.type)
        return static_cast<int>(type) < static_cast<int>(other.type);

    switch (type)
    {
    case HotkeyType::Keyboard:
        return tie(input.key, modifiers) < tie(other.input.key, other.modifiers);
    case HotkeyType::Mouse:
        return tie(input.button, modifiers) < tie(other.input.button, other.modifiers);
    case HotkeyType::Gamepad:
        return tie(input.gamepadButton, modifiers) < tie(other.input.gamepadButton, other.modifiers);
    default:
        return false;
    }
}

bool HotkeyManager::matchesKeyboardHotkey(const Hotkey &hk, const InputEvent &event) const
{
    return event.type == InputEvent::KeyPressed &&
           hk.input.key == event.data.key.key &&
           (hk.modifiers & event.data.key.modifiers) == hk.modifiers;
}

bool HotkeyManager::matchesMouseHotkey(const Hotkey &hk, const InputEvent &event) const
{
    return event.type == InputEvent::MouseButtonPressed &&
           hk.input.button == event.data.mouseButton.button &&
           (hk.modifiers & event.data.mouseButton.modifiers) == hk.modifiers;
}

void HotkeyManager::processEvents(const vector<InputEvent> &events)
{
    for (const auto &event : events)
    {
        // Обработка горячих клавиш
        for (const auto &[hotkey, callback] : hotkeyCallbacks)
        {
            bool match = false;

            switch (hotkey.type)
            {
            case HotkeyType::Keyboard:
                match = matchesKeyboardHotkey(hotkey, event);
                break;

            case HotkeyType::Mouse:
                match = matchesMouseHotkey(hotkey, event);
                break;

            // Для других типов можно добавить обработку
            default:
                break;
            }

            if (match)
            {
                callback();
                //break; // Прерываем после первого совпадения
            }
        }

        // Обработка кликов мыши
        if (event.type == InputEvent::MouseButtonPressed)
        {
            auto it = clickCallbacks.find(event.data.mouseButton.button);
            if (it != clickCallbacks.end())
            {
                it->second();
            }
        }

        // Обработка движения мыши
        if (event.type == InputEvent::MouseMoved && mouseMoveCallback)
        {
            mouseMoveCallback(event.data.mouseMove.x, event.data.mouseMove.y);
        }

        // Обработка колеса мыши
        if (event.type == InputEvent::MouseWheel && mouseWheelCallback)
        {
            mouseWheelCallback(event.data.mouseWheel.x, event.data.mouseWheel.y);
        }
    }
}