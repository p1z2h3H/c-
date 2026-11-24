#include "Point.hpp"

namespace adas
{
Point::Point(std::int32_t x, std::int32_t y) noexcept : x(x), y(y)
{
}

Point& Point::operator+=(const Point& other) noexcept
{
    x += other.x;
    y += other.y;
    return *this;
}

Point& Point::operator-=(const Point& other) noexcept
{
    x -= other.x;
    y -= other.y;
    return *this;
}

std::int32_t Point::GetX() const noexcept
{
    return x;
}

std::int32_t Point::GetY() const noexcept
{
    return y;
}
}  // namespace adas
