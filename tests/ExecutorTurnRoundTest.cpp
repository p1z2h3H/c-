#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"
#include "command/CmderFactory.hpp"
namespace adas
{
TEST(ExecutorTurnRoundTest, should_turn_round_in_all_drive_modes)
{
    const struct {
        const char* commands;
        Pose expected;
    } cases[] = {
        {"TR", {0, 1, 'W'}},
        {"FTR", {1, 1, 'W'}},
        {"BTR", {0, 1, 'W'}},
        {"BFTR", {1, 1, 'W'}},
    };

    for (const auto& testCase : cases) {
        SCOPED_TRACE(testCase.commands);
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
        ASSERT_NE(nullptr, executor.get());

        executor->Execute(testCase.commands);

        EXPECT_EQ(testCase.expected, executor->Query());
    }
}
TEST(ExecutorTurnRoundTest, should_execute_both_adjacent_turn_round_commands)
{
    const CmderFactory factory;
    const auto handlers = factory.GetCmders("TRTR");
    ASSERT_EQ(2U, handlers.size());

    PoseHandler state({0, 0, 'E'});
    handlers[0](state).DoOperate(state);
    const Pose afterFirst{0, 1, 'W'};
    EXPECT_EQ(afterFirst, state.Query());

    handlers[1](state).DoOperate(state);
    const Pose afterSecond{0, 0, 'E'};
    EXPECT_EQ(afterSecond, state.Query());
}
}  // namespace adas