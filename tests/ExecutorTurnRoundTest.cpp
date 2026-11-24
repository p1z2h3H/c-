#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

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
}  // namespace adas