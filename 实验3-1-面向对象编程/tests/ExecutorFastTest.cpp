#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{

TEST(ExecutorFastTest, should_move_two_steps_when_fast)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("FM");

    const Pose expected{2, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorFastTest, should_move_before_turning_left_when_fast)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("FL");

    const Pose expected{1, 0, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorFastTest, should_move_before_turning_right_when_fast)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("FR");

    const Pose expected{1, 0, 'S'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorFastTest, should_cancel_fast_after_second_F)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("FFM");

    const Pose expected{0, 1, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorFastTest, should_keep_fast_state_between_execute_calls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("F");

    const Pose afterFast{0, 0, 'E'};
    ASSERT_EQ(afterFast, executor->Query());

    executor->Execute("M");

    const Pose afterMove{2, 0, 'E'};
    ASSERT_EQ(afterMove, executor->Query());
}

TEST(ExecutorFastTest, should_return_to_normal_speed_after_toggling_off)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("FMFM");

    const Pose expected{3, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

}  // namespace adas