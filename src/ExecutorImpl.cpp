#include "ExecutorImpl.hpp"

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
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const char command : commands) {
        if (command == 'M') {
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
        } else if (command == 'L') {
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
        } else if (command == 'R') {
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
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
