#pragma once

#include <cstddef>
#include <string_view>

#include "Point.hpp"

namespace adas
{
class Direction
{
public:
    explicit Direction(char heading) noexcept : index{headings.find(heading)}
    {
    }

    char GetHeading() const noexcept
    {
        return headings[index];
    }

    Point Step() const noexcept
    {
        static const Point steps[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        return steps[index];
    }

    void TurnLeft() noexcept
    {
        index = (index + 3) % 4;
    }
    void TurnRight() noexcept
    {
        index = (index + 1) % 4;
    }

private:
    static constexpr std::string_view headings{"NESW"};
    std::size_t index;
};
}  // namespace adas