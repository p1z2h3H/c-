#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

namespace adas
{

class ExecutorImpl : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose = {0, 0, 'N'}) noexcept;

    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    PoseHandler poseHandler;
};
}  // namespace adas
