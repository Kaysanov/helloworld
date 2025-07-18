#pragma once
#include <string>
#include <unordered_map>
#include <algorithm>
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

// Преобразование в нижний регистр
static std::string toLower(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}

// Маппинг строка -> enum (инициализируется один раз)
static const auto MouseButtonFromString = std::unordered_map<std::string, MouseButton>{
    {"none", MouseButton::None},
    {"left", MouseButton::Left},
    {"right", MouseButton::Right},
    {"middle", MouseButton::Middle},
    {"extra1", MouseButton::Extra1},
    {"extra2", MouseButton::Extra2}};

static const auto StringFromMouseButton = std::unordered_map<MouseButton, std::string>{
    {MouseButton::None, "None"},
    {MouseButton::Left, "Left"},
    {MouseButton::Right, "Right"},
    {MouseButton::Middle, "Middle"},
    {MouseButton::Extra1, "Extra1"},
    {MouseButton::Extra2, "Extra2"}};

// Преобразование строки в MouseButton (статический метод)
static MouseButton MouseButtonfromString(const std::string &str)
{
    std::string lower = toLower(str);
    auto it = MouseButtonFromString.find(lower);

    if (it != MouseButtonFromString.end())
    {
        return MouseButton(it->second);
    }
    return  MouseButton::None;
}

// Преобразование в строку
static std::string MouseButtontoString(MouseButton value) 
{
    auto it = StringFromMouseButton.find(value);
    if (it != StringFromMouseButton.end())
    {
        return it->second;
    }
    return "None";
}
