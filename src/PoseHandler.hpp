#pragma once
#include "Executor.hpp"
#include "Point.hpp"

namespace adas
{
class PoseHandler
{
public:
    explicit PoseHandler(const Pose& initialPose) noexcept;
    Pose Query() const noexcept;
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;

private:
    Point point;
    char heading;
    bool fast{false};
};
}  // namespace adas