#include "ExecutorImpl.hpp"

#include <new>

#include "CmderFactory.hpp"
#include "Singleton.hpp"

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