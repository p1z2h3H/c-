#pragma once
#include "action/ActionGroup.hpp"
#include "core/PoseHandler.hpp"

namespace adas
{

inline ActionType MovementAction(const PoseHandler& state) noexcept
{
    return state.IsReverse() ? ActionType::Backward : ActionType::Forward;
}

inline ActionGroup MakeTurnGroup(const PoseHandler& state, ActionType normalTurn, ActionType reverseTurn)
{
    const auto type = state.GetVehicleType();
    const auto step = MovementAction(state);
    const int stepsBeforeTurn = (type == VehicleType::Bus ? 1 : 0) + (state.IsFast() ? 1 : 0);

    ActionGroup group;
    for (int index = 0; index < stepsBeforeTurn; ++index) {
        group.Add(step);
    }

    group.Add(state.IsReverse() ? reverseTurn : normalTurn);

    if (type == VehicleType::Sport) {
        group.Add(step);
    }
    return group;
}

class MoveCommand final
{
public:
    ActionGroup operator()(const PoseHandler& state) const
    {
        const auto step = MovementAction(state);
        const int normalSteps = state.GetVehicleType() == VehicleType::Sport ? 2 : 1;
        const int steps = state.IsFast() ? normalSteps * 2 : normalSteps;

        ActionGroup group;
        for (int index = 0; index < steps; ++index) {
            group.Add(step);
        }
        return group;
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(const PoseHandler& state) const
    {
        return MakeTurnGroup(state, ActionType::TurnLeft, ActionType::ReverseTurnLeft);
    }
};

class TurnRightCommand final
{
public:
    ActionGroup operator()(const PoseHandler& state) const
    {
        return MakeTurnGroup(state, ActionType::TurnRight, ActionType::ReverseTurnRight);
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