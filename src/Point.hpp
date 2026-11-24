#pragma once

#include <cstdint>

namespace adas
{
class Point
{
public:
    Point(std::int32_t x, std::int32_t y) noexcept : x{x}, y{y}
    {
    }

    Point& operator+=(const Point& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    std::int32_t GetX() const noexcept
    {
        return x;
    }
    std::int32_t GetY() const noexcept
    {
        return y;
    }

private:
    std::int32_t x;
    std::int32_t y;
};
}  // namespace adas