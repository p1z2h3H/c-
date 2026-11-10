#include <gtest/gtest.h>

#include <memory>
#include <tuple>

#include "Executor.hpp"
namespace adas
{
bool operator==(const Pose& lhs, const Pose& rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
}
TEST(ExecutorTest, should_return_initial_pose_without_commands)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    const Pose expected{2, 3, 'E'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_return_default_pose)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    ASSERT_NE(nullptr, executor.get());

    const Pose expected{0, 0, 'N'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_move_east_when_command_is_M)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose expected{1, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_move_west_when_command_is_M)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose expected{-1, 0, 'W'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_move_north_when_command_is_M)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose expected{0, 1, 'N'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_move_south_when_command_is_M)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose expected{0, -1, 'S'};
    ASSERT_EQ(expected, executor->Query());
}
}  // namespace adas