#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas {

TEST(ExecutorStateTest, should_preserve_fast_reverse_across_calls_and_keep_instances_independent)
{
    std::unique_ptr<Executor> first(Executor::NewExecutor({0, 0, 'E'}));
    std::unique_ptr<Executor> second(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, first.get());
    ASSERT_NE(nullptr, second.get());
    first->Execute("FB");
    first->Execute("M");
    second->Execute("M");
    const Pose firstExpected{-2, 0, 'E'};
    const Pose secondExpected{1, 0, 'E'};
    EXPECT_EQ(firstExpected, first->Query());
    EXPECT_EQ(secondExpected, second->Query());
    first->Execute("FBM");
    const Pose resetExpected{-1, 0, 'E'};
    EXPECT_EQ(resetExpected, first->Query());
}

TEST(ExecutorStateTest, should_toggle_reverse_without_changing_pose_and_cancel_after_two_Bs)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, -3, 'S'}));
    ASSERT_NE(nullptr, executor.get());
    executor->Execute("B");
    const Pose initial{2, -3, 'S'};
    EXPECT_EQ(initial, executor->Query());
    executor->Execute("BM");
    const Pose expected{2, -4, 'S'};
    EXPECT_EQ(expected, executor->Query());
}

}  // namespace adas
