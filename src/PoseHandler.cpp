#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& initialPose) noexcept : pose{initialPose}
{
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}
void PoseHandler::Move() noexcept
{
    switch (pose.heading) {
    case 'N':
        ++pose.y;
        break;
    case 'S':
        --pose.y;
        break;
    case 'E':
        ++pose.x;
        break;
    case 'W':
        --pose.x;
        break;
    }
}
void PoseHandler::TurnLeft() noexcept
{
    switch (pose.heading) {
    case 'N':
        pose.heading = 'W';
        break;
    case 'W':
        pose.heading = 'S';
        break;
    case 'S':
        pose.heading = 'E';
        break;
    case 'E':
        pose.heading = 'N';
        break;
    }
}
void PoseHandler::TurnRight() noexcept
{
    switch (pose.heading) {
    case 'N':
        pose.heading = 'E';
        break;
    case 'E':
        pose.heading = 'S';
        break;
    case 'S':
        pose.heading = 'W';
        break;
    case 'W':
        pose.heading = 'N';
        break;
    }
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