#include "ExecutorImpl.hpp"

#include <memory>
#include <new>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : poseHandler{initialPose}
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const char command : commands) {
        std::unique_ptr<ICommand> cmder;

        if (command == 'M') {
            cmder = std::make_unique<MoveCommand>();
        } else if (command == 'L') {
            cmder = std::make_unique<TurnLeftCommand>();
        } else if (command == 'R') {
            cmder = std::make_unique<TurnRightCommand>();
        } else if (command == 'F') {
            cmder = std::make_unique<FastCommand>();
        }

        if (cmder) {
            cmder->DoOperate(poseHandler);
        }
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
