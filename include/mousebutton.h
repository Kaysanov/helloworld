#pragma once
#include <string>
#include <unordered_map>
#include <algorithm>
#include <string_view>
#include "StringUtils.h"
#include <stdexcept>
#include <cctype>

enum class MouseButton
{
    None,
    Left,
    Right,
    Middle,
    Extra1,
    Extra2
};

// Маппинг строка -> enum (инициализируется один раз)
inline const auto MouseButtonFromStringMap = std::unordered_map<std::string, MouseButton>{
    {"none", MouseButton::None},
    {"left", MouseButton::Left},
    {"right", MouseButton::Right},
    {"middle", MouseButton::Middle},
    {"extra1", MouseButton::Extra1},
    {"extra2", MouseButton::Extra2}};

inline const auto StringFromMouseButtonMap = std::unordered_map<MouseButton, std::string>{
    {MouseButton::None, "None"},
    {MouseButton::Left, "Left"},
    {MouseButton::Right, "Right"},
    {MouseButton::Middle, "Middle"},
    {MouseButton::Extra1, "Extra1"},
    {MouseButton::Extra2, "Extra2"}};

// Преобразование строки в MouseButton (статический метод)
inline MouseButton MouseButtonfromString(std::string_view str)
{
    std::string lower = StringUtils::toLower(str); // toLower создаст строку
    auto it = MouseButtonFromStringMap.find(lower);

    if (it != MouseButtonFromStringMap.end())
    {
        return MouseButton(it->second);
    }
    return  MouseButton::None;
}

// Преобразование в строку
inline std::string MouseButtonToString(MouseButton value) 
{
    auto it = StringFromMouseButtonMap.find(value);
    if (it != StringFromMouseButtonMap.end())
    {
        return it->second;
    }
    return "None";
}
