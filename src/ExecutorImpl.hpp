#pragma once

#include "Executor.hpp"

namespace adas
{

class ExecutorImpl : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose = {0, 0, 'N'}) noexcept;

    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

    Pose pose;
};
}  // namespace adas
