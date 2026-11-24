#pragma once
#include "ActionGroup.hpp"
#include "PoseHandler.hpp"

namespace adas
{

class MoveCommand final
{
public:
    void operator()(PoseHandler& state) const noexcept
    {
        if (state.IsFast()) {
            state.Move();
        }

        state.Move();
    }
};

class TurnLeftCommand final
{
public:
    void operator()(PoseHandler& state) const noexcept
    {
        if (state.IsFast()) {
            state.Move();
        }

        if (state.IsReverse()) {
            state.TurnRight();
        } else {
            state.TurnLeft();
        }
    }
};

class TurnRightCommand final
{
public:
    void operator()(PoseHandler& state) const noexcept
    {
        if (state.IsFast()) {
            state.Move();
        }

        if (state.IsReverse()) {
            state.TurnLeft();
        } else {
            state.TurnRight();
        }
    }
};

class FastCommand final
{
public:
    void operator()(PoseHandler& state) const noexcept
    {
        state.Fast();
    }
};
class ReverseCommand final
{
public:
    void operator()(PoseHandler& state) const noexcept
    {
        state.Reverse();
    }
};

class TurnRoundCommand final
{
public:
    ActionGroup operator()(const PoseHandler& state) const
    {
        if (state.IsFast()) {
            return ActionGroup{ActionType::Forward, ActionType::TurnLeft, ActionType::Forward, ActionType::TurnLeft};
        }

        return ActionGroup{ActionType::TurnLeft, ActionType::Forward, ActionType::TurnLeft};
    }
};
}  // namespace adas