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
    if (reverse) {
        point -= direction.Step();
    } else {
        Forward();
    }
}

void PoseHandler::Forward() noexcept
{
    point += direction.Step();
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