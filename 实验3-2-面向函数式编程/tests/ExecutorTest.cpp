#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"
namespace adas
{
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
TEST(ExecutorTest, should_face_west_when_turning_left_from_north)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose expected{2, 3, 'W'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_face_south_when_turning_left_from_west)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'W'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose expected{2, 3, 'S'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_face_east_when_turning_left_from_south)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'S'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose expected{2, 3, 'E'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_face_north_when_turning_left_from_east)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose expected{2, 3, 'N'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_face_east_when_turning_right_from_north)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose expected{2, 3, 'E'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_face_south_when_turning_right_from_east)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose expected{2, 3, 'S'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_face_west_when_turning_right_from_south)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'S'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose expected{2, 3, 'W'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_face_north_when_turning_right_from_west)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'W'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose expected{2, 3, 'N'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_execute_commands_in_order)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("MLMMRM");

    const Pose expected{-2, 2, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_keep_pose_when_commands_are_empty)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));

    ASSERT_NE(nullptr, executor.get());

    executor->Execute("");

    const Pose expected{2, 3, 'E'};
    ASSERT_EQ(expected, executor->Query());
}
}  // namespace adas