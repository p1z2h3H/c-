#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
TEST(ExecutorReverseTest, should_move_backward_when_reverse_is_enabled)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("BM");

    const Pose expected{0, -1, 'N'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorReverseTest, should_reverse_turn_direction_and_keep_move_order)
{
    const struct {
        const char* commands;
        Pose expected;
    } cases[] = {
        {"BL", {0, 0, 'E'}},
        {"BR", {0, 0, 'W'}},
        {"BFL", {0, -1, 'E'}},
        {"BFR", {0, -1, 'W'}},
    };

    for (const auto& testCase : cases) {
        SCOPED_TRACE(testCase.commands);
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
        ASSERT_NE(nullptr, executor.get());

        executor->Execute(testCase.commands);

        EXPECT_EQ(testCase.expected, executor->Query());
    }
}
}  // namespace adas