#include <gtest/gtest.h>

#include <array>
#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas {

TEST(ExecutorTurnRoundTest, should_follow_TR_rules_for_every_vehicle_state_and_heading)
{
    struct StateCase {
        const char* prefix;
        bool fast;
    };
    const std::array<StateCase, 4> states{{{"", false}, {"B", false}, {"F", true}, {"BF", true}}};
    const std::array<Pose, 4> normal{{{0, 1, 'W'}, {-1, 0, 'S'}, {0, -1, 'E'}, {1, 0, 'N'}}};
    const std::array<Pose, 4> fast{{{1, 1, 'W'}, {-1, 1, 'S'}, {-1, -1, 'E'}, {1, -1, 'N'}}};
    const std::string headings = "ENWS";

    for (const auto type : {VehicleType::Normal, VehicleType::Sport, VehicleType::Bus}) {
        for (const auto& state : states) {
            for (unsigned heading = 0; heading < headings.size(); ++heading) {
                const auto commands = std::string(state.prefix) + "TR";
                SCOPED_TRACE(commands + " heading " + headings[heading]);
                std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, headings[heading]}, type));
                ASSERT_NE(nullptr, executor.get());
                executor->Execute(commands);
                EXPECT_EQ(state.fast ? fast[heading] : normal[heading], executor->Query());
            }
        }
    }
}

TEST(ExecutorTurnRoundTest, should_parse_adjacent_TR_commands_as_two_complete_commands)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());
    executor->Execute("TRTR");
    const Pose expected{0, 0, 'E'};
    EXPECT_EQ(expected, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_keep_reverse_state_after_TR)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());
    executor->Execute("BTR");
    executor->Execute("M");
    const Pose expected{1, 1, 'W'};
    EXPECT_EQ(expected, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_keep_fast_reverse_state_after_TR)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());
    executor->Execute("BFTR");
    executor->Execute("M");
    const Pose expected{3, 1, 'W'};
    EXPECT_EQ(expected, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_execute_mixed_commands_and_state_changes_in_order)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());
    executor->Execute("MTRFMBTR");
    const Pose expected{-2, 0, 'E'};
    EXPECT_EQ(expected, executor->Query());
}

}  // namespace adas
