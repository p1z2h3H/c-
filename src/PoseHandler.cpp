#include "PoseHandler.hpp"

namespace adas
{

PoseHandler::PoseHandler(const Pose& initialPose) noexcept
    : point{initialPose.x, initialPose.y}, heading{initialPose.heading}
{
}

Pose PoseHandler::Query() const noexcept
{
    return {point.GetX(), point.GetY(), heading};
}

void PoseHandler::Move() noexcept
{
    switch (heading) {
    case 'N':
        point += Point{0, 1};
        break;
    case 'S':
        point += Point{0, -1};
        break;
    case 'E':
        point += Point{1, 0};
        break;
    case 'W':
        point += Point{-1, 0};
        break;
    }
}
void PoseHandler::TurnLeft() noexcept
{
    switch (heading) {
    case 'N':
        heading = 'W';
        break;
    case 'W':
        heading = 'S';
        break;
    case 'S':
        heading = 'E';
        break;
    case 'E':
        heading = 'N';
        break;
    }
}
void PoseHandler::TurnRight() noexcept
{
    switch (heading) {
    case 'N':
        heading = 'E';
        break;
    case 'E':
        heading = 'S';
        break;
    case 'S':
        heading = 'W';
        break;
    case 'W':
        heading = 'N';
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