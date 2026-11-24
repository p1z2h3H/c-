#include "ExecutorImpl.hpp"

#include <functional>
#include <new>
#include <unordered_map>

#include "Command.hpp"

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
    using CommandHandler = std::function<void(PoseHandler&)>;
    static const std::unordered_map<char, CommandHandler> commandMap{
        {'M', MoveCommand{}}, {'L', TurnLeftCommand{}}, {'R', TurnRightCommand{}},
        {'F', FastCommand{}}, {'B', ReverseCommand{}},
    };

    for (std::string::size_type index = 0; index < commands.size(); ++index) {
        const char command = commands[index];

        if (command == 'T' && index + 1 < commands.size() && commands[index + 1] == 'R') {
            TurnRoundCommand{}(poseHandler);
            ++index;
            continue;
        }

        const auto found = commandMap.find(command);
        if (found != commandMap.end()) {
            found->second(poseHandler);
        }
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
