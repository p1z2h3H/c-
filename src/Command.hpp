#pragma once
#include "ActionGroup.hpp"
#include "PoseHandler.hpp"

namespace adas
{

inline ActionType MovementAction(const PoseHandler& state) noexcept
{
    return state.IsReverse() ? ActionType::Backward : ActionType::Forward;
}

class MoveCommand final
{
public:
    ActionGroup operator()(const PoseHandler& state) const
    {
        const auto step = MovementAction(state);
        return state.IsFast() ? ActionGroup{step, step} : ActionGroup{step};
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(const PoseHandler& state) const
    {
        const auto turn = state.IsReverse() ? ActionType::ReverseTurnLeft : ActionType::TurnLeft;
        return state.IsFast() ? ActionGroup{MovementAction(state), turn} : ActionGroup{turn};
    }
};

class TurnRightCommand final
{
public:
    ActionGroup operator()(const PoseHandler& state) const
    {
        const auto turn = state.IsReverse() ? ActionType::ReverseTurnRight : ActionType::TurnRight;
        return state.IsFast() ? ActionGroup{MovementAction(state), turn} : ActionGroup{turn};
    }
};

class FastCommand final
{
public:
    ActionGroup operator()(const PoseHandler&) const
    {
        return ActionGroup{ActionType::ToggleFast};
    }
};

class ReverseCommand final
{
public:
    ActionGroup operator()(const PoseHandler&) const
    {
        return ActionGroup{ActionType::ToggleReverse};
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