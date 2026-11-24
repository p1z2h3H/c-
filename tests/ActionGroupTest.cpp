#include <gtest/gtest.h>

#include <vector>

#include "Executor.hpp"
#include "PoseEq.hpp"
#include "action/ActionGroup.hpp"
#include "command/Command.hpp"
#include "core/PoseHandler.hpp"

namespace adas {

TEST(ActionGroupTest, should_keep_fast_sport_movement_as_four_single_steps)
{
    PoseHandler state({0, 0, 'E'}, VehicleType::Sport);
    state.Fast();
    const auto group = MoveCommand()(state);
    const std::vector<ActionType> expected(4, ActionType::ForwardOneStep);
    EXPECT_EQ(expected, group.GetActions());
    const Pose before{0, 0, 'E'};
    EXPECT_EQ(before, state.Query());
    group.DoOperate(state);
    const Pose after{4, 0, 'E'};
    EXPECT_EQ(after, state.Query());
}

TEST(ActionGroupTest, should_plan_fast_reverse_sport_turn_in_required_order)
{
    PoseHandler state({0, 0, 'E'}, VehicleType::Sport);
    state.Fast();
    state.Reverse();
    const auto group = TurnLeftCommand()(state);
    const std::vector<ActionType> expected{
        ActionType::BackwardOneStep, ActionType::ReverseTurnLeft, ActionType::BackwardOneStep};
    EXPECT_EQ(expected, group.GetActions());
}

TEST(ActionGroupTest, should_plan_TR_using_absolute_forward_and_left_actions)
{
    PoseHandler state({0, 0, 'E'});
    state.Fast();
    state.Reverse();
    const auto group = TurnRoundCommand()(state);
    const std::vector<ActionType> expected{
        ActionType::ForwardOneStep, ActionType::TurnLeft,
        ActionType::ForwardOneStep, ActionType::TurnLeft};
    EXPECT_EQ(expected, group.GetActions());
}

TEST(ActionGroupTest, should_execute_state_and_motion_actions_in_sequence)
{
    PoseHandler state({0, 0, 'N'});
    const ActionGroup group{ActionType::ToggleFast, ActionType::ToggleReverse,
                            ActionType::BackwardOneStep, ActionType::ReverseTurnLeft};
    group.DoOperate(state);
    EXPECT_TRUE(state.IsFast());
    EXPECT_TRUE(state.IsReverse());
    const Pose expected{0, -1, 'E'};
    EXPECT_EQ(expected, state.Query());
}

}  // namespace adas
