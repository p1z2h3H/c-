#pragma once

#include <cstddef>

#include "Point.hpp"

namespace adas
{
class Direction final
{
public:
    static const Direction& GetDirection(char heading) noexcept;

    const Point& Move() const noexcept;
    const Direction& LeftOne() const noexcept;
    const Direction& RightOne() const noexcept;
    char GetHeading() const noexcept;

private:
    Direction(std::size_t index, char heading, const Point& movement) noexcept;

    static const Direction directions[4];
    std::size_t index;
    char heading;
    Point movement;
};
}  // namespace adas
