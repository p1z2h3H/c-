#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& initialPose, VehicleType type) noexcept
    : point{initialPose.x, initialPose.y}, direction{initialPose.heading}, vehicleType{type}
{
}

Pose PoseHandler::Query() const noexcept
{
    return {point.GetX(), point.GetY(), direction.GetHeading()};
}

void PoseHandler::Backward() noexcept
{
    point -= direction.Step();
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