#pragma once
#include <string>
#include <algorithm>
#include <string_view>
#include <cctype>

namespace StringUtils
{
    // Преобразование в нижний регистр
    inline std::string toLower(const std::string &str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    // Перегрузка для string_view
    inline std::string toLower(std::string_view str)
    {
        std::string result(str);
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }
} // namespace StringUtils