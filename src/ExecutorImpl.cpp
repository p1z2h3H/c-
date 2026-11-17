#include "ExecutorImpl.hpp"

#include <memory>
#include <new>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : pose{initialPose}
{
}
void ExecutorImpl::Move() noexcept
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
void ExecutorImpl::TurnLeft() noexcept
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
void ExecutorImpl::TurnRight() noexcept
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
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const char command : commands) {
        if (command == 'M') {
            std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();

            cmder->DoOperate(*this);
        } else if (command == 'L') {
            std::unique_ptr<TurnLeftCommand> cmder = std::make_unique<TurnLeftCommand>();

            cmder->DoOperate(*this);
        } else if (command == 'R') {
            std::unique_ptr<TurnRightCommand> cmder = std::make_unique<TurnRightCommand>();

            cmder->DoOperate(*this);
        }
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
