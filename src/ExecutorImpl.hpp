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
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void DoOperate(PoseHandler& state) const noexcept = 0;
    };

    class MoveCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler& state) const noexcept override
        {
            if (state.IsFast()) {
                state.Move();
            }

            state.Move();
        }
    };

    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler& state) const noexcept override
        {
            if (state.IsFast()) {
                state.Move();
            }

            state.TurnLeft();
        }
    };

    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler& state) const noexcept override
        {
            if (state.IsFast()) {
                state.Move();
            }

            state.TurnRight();
        }
    };

    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler& state) const noexcept override
        {
            state.Fast();
        }
    };

    PoseHandler poseHandler;
};
}  // namespace adas
