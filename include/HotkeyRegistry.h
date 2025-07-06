#pragma once
#include "InputTypes.h"
#include <functional>
#include <unordered_map>
#include <cstddef> // Для size_t
#include <fmt/core.h>

class HotkeyRegistry
{
public:
    struct Hotkey
    {
        HotkeyType type = HotkeyType::Keyboard;
        uint16_t modifiers = 0;

        union
        {
            Key key = Key::Unknown;
            MouseButton button;
            int gamepadButton;
        } input;

        bool operator==(const Hotkey &other) const
        {
            if (type != other.type || modifiers != other.modifiers)
                return false;

            switch (type)
            {
            case HotkeyType::Keyboard:
                return input.key == other.input.key;
            case HotkeyType::Mouse:
                return input.button == other.input.button;
            case HotkeyType::Gamepad:
                return input.gamepadButton == other.input.gamepadButton;
            default:
                return true;
            }
        }

        struct Hash
        {
            size_t operator()(const Hotkey &hk) const
            {
                size_t seed = 0;

                // Хеш-комбинатор
                auto hash_combine = [](size_t &seed, auto value)
                {
                    seed ^= std::hash<decltype(value)>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                };

                // Комбинируем поля
                hash_combine(seed, static_cast<int>(hk.type));
                hash_combine(seed, hk.modifiers);

                switch (hk.type)
                {
                case HotkeyType::Keyboard:
                    hash_combine(seed, static_cast<int>(hk.input.key));
                    break;
                case HotkeyType::Mouse:
                    hash_combine(seed, static_cast<int>(hk.input.button));
                    break;
                case HotkeyType::Gamepad:
                    hash_combine(seed, hk.input.gamepadButton);
                    break;
                default:
                    hash_combine(seed, 0xDEADBEEF);
                }
                return seed;
            }
        };

        std::string to_string()
        {
            std::string result;
            //result += fmt::format("{}", static_cast<int>(type));
            //result += itostring(modifiers);
            result += static_cast<int>(type);
            result += static_cast<int>(modifiers);

            return result;
        };
    };

    
    void registerMouseHotkey(InputState state, MouseButton button, uint16_t modifiers, std::function<void()> callback);
    // Новые методы для событий отпускания
    
    void registerMouseRelease(InputState state, MouseButton button, uint16_t modifiers, std::function<void()> callback);

     // Регистрация с учётом состояния
    void registerKeyboardHotkey(InputState state, Key key, uint16_t modifiers, std::function<void()> callback);
    void registerKeyboardRelease(InputState state, Key key, uint16_t modifiers, std::function<void()> callback);

    // Новые методы для состояний
    void setKeyState(Key key, bool state);
    bool isKeyDown(Key key) const;
    void setMouseButtonState(MouseButton button, bool state);
    bool isMouseButtonDown(MouseButton button) const;

     // Поиск с учётом состояния
    std::function<void()> findCallback(InputState state, const Hotkey& hk) const;
    std::function<void()> findReleaseCallback(InputState state, const Hotkey& hk) const;

private:
    //std::unordered_map<Hotkey, std::function<void()>, Hotkey::Hash> callbacks_;
    //std::unordered_map<Hotkey, std::function<void()>, Hotkey::Hash> releaseCallbacks_;
    // Многомерные карты для состояний
    std::array<std::unordered_map<Hotkey, std::function<void()>, Hotkey::Hash>, INPUT_STATE_COUNT> stateCallbacks_;
    std::array<std::unordered_map<Hotkey, std::function<void()>, Hotkey::Hash>, INPUT_STATE_COUNT> stateReleaseCallbacks_;
    std::unordered_map<Key, bool> keyStates_;
    std::unordered_map<MouseButton, bool> mouseButtonStates_;
};

// Реализация форматирования для fmt
/*template <typename Char>
struct fmt::formatter<HotkeyRegistry::Hotkey, Char> : fmt::formatter<std::string_view, Char>
{
    // Используем базовый форматтер для std::string_view
    auto format(const HotkeyRegistry::Hotkey &hk, format_context &ctx)
    {
        return fmt::vformat_to(ctx.out(), "{}", hk.to_string());
    }
};
*/