#include "Command.hpp"

#include <array>
#include <cstddef>

#include "core/PoseHandler.hpp"

namespace adas {
namespace {

struct VehicleBehavior {
    unsigned moveSteps;
    unsigned stepsBeforeTurn;
    unsigned stepsAfterTurn;
};

const VehicleBehavior& GetBehavior(VehicleType type) noexcept
{
    static constexpr std::array<VehicleBehavior, 3> behaviors{{
        {1, 0, 0},  // Normal
        {2, 0, 1},  // Sport
        {1, 1, 0}   // Bus
    }};
    return behaviors[static_cast<std::size_t>(type)];
}

ActionGroup BuildTurn(const PoseHandler& state, ActionType normalTurn, ActionType reverseTurn)
{
    const auto& behavior = GetBehavior(state.GetVehicleType());
    const auto movement = state.IsReverse() ? ActionType::BackwardOneStep : ActionType::ForwardOneStep;
    const unsigned stepsBefore = behavior.stepsBeforeTurn + (state.IsFast() ? 1U : 0U);
    ActionGroup group;
    for (unsigned step = 0; step < stepsBefore; ++step) {
        group.PushAction(movement);
    }
    group.PushAction(state.IsReverse() ? reverseTurn : normalTurn);
    for (unsigned step = 0; step < behavior.stepsAfterTurn; ++step) {
        group.PushAction(movement);
    }
    return group;
}

}  // namespace

ActionGroup MoveCommand::operator()(const PoseHandler& state) const
{
    const unsigned steps = GetBehavior(state.GetVehicleType()).moveSteps * (state.IsFast() ? 2U : 1U);
    const auto movement = state.IsReverse() ? ActionType::BackwardOneStep : ActionType::ForwardOneStep;
    ActionGroup group;
    for (unsigned step = 0; step < steps; ++step) {
        group.PushAction(movement);
    }
    return group;
}

ActionGroup TurnLeftCommand::operator()(const PoseHandler& state) const
{
    return BuildTurn(state, ActionType::TurnLeft, ActionType::ReverseTurnLeft);
}

ActionGroup TurnRightCommand::operator()(const PoseHandler& state) const
{
    return BuildTurn(state, ActionType::TurnRight, ActionType::ReverseTurnRight);
}

ActionGroup FastCommand::operator()(const PoseHandler&) const
{
    return {ActionType::ToggleFast};
}

ActionGroup ReverseCommand::operator()(const PoseHandler&) const
{
    return {ActionType::ToggleReverse};
}

ActionGroup TurnRoundCommand::operator()(const PoseHandler& state) const
{
    if (state.IsFast()) {
        return {ActionType::ForwardOneStep, ActionType::TurnLeft,
                ActionType::ForwardOneStep, ActionType::TurnLeft};
    }
    return {ActionType::TurnLeft, ActionType::ForwardOneStep, ActionType::TurnLeft};
}

}  // namespace adas
