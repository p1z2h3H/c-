#pragma once

#include "Point.hpp"

namespace adas {

class Direction final {
public:
    explicit Direction(char heading) noexcept;
    const Point& Move() const noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    char GetHeading() const noexcept;

private:
    unsigned index;
};

}  // namespace adas
