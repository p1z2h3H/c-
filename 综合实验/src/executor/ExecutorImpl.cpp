#include "ExecutorImpl.hpp"

#include <algorithm>
#include <new>

#include "command/CmderFactory.hpp"
#include "common/Singleton.hpp"

namespace adas {

Executor* Executor::NewExecutor(const Pose& pose, VehicleType type) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose, type);
}

ExecutorImpl::ExecutorImpl(const Pose& pose, VehicleType type) noexcept : poseHandler(pose, type) {}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);
    std::for_each(cmders.begin(), cmders.end(), [this](const Cmder& cmder) {
        cmder(poseHandler).DoOperate(poseHandler);
    });
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}

}  // namespace adas
