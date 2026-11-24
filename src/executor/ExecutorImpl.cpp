#include "ExecutorImpl.hpp"

#include <new>

#include "command/CmderFactory.hpp"
#include "common/Singleton.hpp"

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose, VehicleType type) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose, type);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose, VehicleType type) noexcept : poseHandler{initialPose, type}
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const auto& factory = Singleton<CmderFactory>::Instance();
    const auto handlers = factory.GetCmders(commands);

    for (const auto& handler : handlers) {
        handler(poseHandler).DoOperate(poseHandler);
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas