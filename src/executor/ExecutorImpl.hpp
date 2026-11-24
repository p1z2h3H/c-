#pragma once

#include "Executor.hpp"
#include "core/PoseHandler.hpp"

namespace adas {

class ExecutorImpl final : public Executor {
public:
    ExecutorImpl(const Pose& pose, VehicleType type) noexcept;
    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    PoseHandler poseHandler;
};

}  // namespace adas
