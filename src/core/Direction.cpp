#include "Direction.hpp"

#include <array>
#include <string_view>

namespace adas {
namespace {
constexpr std::string_view HEADINGS{"NESW"};
const std::array<Point, 4> STEPS{{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
}

Direction::Direction(char heading) noexcept
    : index(static_cast<unsigned>(HEADINGS.find(heading)))
{
}

const Point& Direction::Move() const noexcept
{
    return STEPS[index];
}

void Direction::TurnLeft() noexcept
{
    index = (index + 3) % 4;
}

void Direction::TurnRight() noexcept
{
    index = (index + 1) % 4;
}

char Direction::GetHeading() const noexcept
{
    return HEADINGS[index];
}

}  // namespace adas
