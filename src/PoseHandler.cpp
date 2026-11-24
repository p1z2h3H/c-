#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& initialPose) noexcept
    : point{initialPose.x, initialPose.y}, direction{initialPose.heading}
{
}

Pose PoseHandler::Query() const noexcept
{
    return {point.GetX(), point.GetY(), direction.GetHeading()};
}

void PoseHandler::Move() noexcept
{
    const Point step = direction.Step();
    if (reverse) {
        point -= step;
    } else {
        point += step;
    }
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}
bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}
void PoseHandler::TurnLeft() noexcept
{
    direction.TurnLeft();
}

void PoseHandler::TurnRight() noexcept
{
    direction.TurnRight();
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}
}  // namespace adas