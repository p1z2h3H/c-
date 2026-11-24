#pragma once

#include "PoseHandler.hpp"

namespace adas
{
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
class ReverseCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& state) const noexcept override
    {
        state.Reverse();
    }
};
}  // namespace adas