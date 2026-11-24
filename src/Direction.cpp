#include "Direction.hpp"

#include <string_view>

namespace adas
{
const Direction Direction::directions[4] = {
    {0, 'N', {0, 1}},
    {1, 'E', {1, 0}},
    {2, 'S', {0, -1}},
    {3, 'W', {-1, 0}},
};

Direction::Direction(std::size_t index, char heading, const Point& movement) noexcept
    : index(index), heading(heading), movement(movement)
{
}

const Direction& Direction::GetDirection(char heading) noexcept
{
    // The public interface guarantees a valid N/E/S/W heading.
    return directions[std::string_view("NESW").find(heading)];
}

const Point& Direction::Move() const noexcept
{
    return movement;
}

const Direction& Direction::LeftOne() const noexcept
{
    return directions[(index + 3) % 4];
}

const Direction& Direction::RightOne() const noexcept
{
    return directions[(index + 1) % 4];
}

char Direction::GetHeading() const noexcept
{
    return heading;
}
}  // namespace adas
