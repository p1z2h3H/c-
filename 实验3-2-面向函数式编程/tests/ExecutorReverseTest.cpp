#include <gtest/gtest.h>

#include <array>
#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
namespace
{
struct ReverseCase {
    const char* name;
    Pose initialPose;
    const char* commands;
    Pose expectedPose;
};

const std::array<ReverseCase, 24> reverseCases{{
    {"EastMove", {0, 0, 'E'}, "BM", {-1, 0, 'E'}},
    {"EastLeft", {0, 0, 'E'}, "BL", {0, 0, 'S'}},
    {"EastRight", {0, 0, 'E'}, "BR", {0, 0, 'N'}},
    {"EastFastMove", {0, 0, 'E'}, "BFM", {-2, 0, 'E'}},
    {"EastFastLeft", {0, 0, 'E'}, "BFL", {-1, 0, 'S'}},
    {"EastFastRight", {0, 0, 'E'}, "BFR", {-1, 0, 'N'}},
    {"NorthMove", {0, 0, 'N'}, "BM", {0, -1, 'N'}},
    {"NorthLeft", {0, 0, 'N'}, "BL", {0, 0, 'E'}},
    {"NorthRight", {0, 0, 'N'}, "BR", {0, 0, 'W'}},
    {"NorthFastMove", {0, 0, 'N'}, "BFM", {0, -2, 'N'}},
    {"NorthFastLeft", {0, 0, 'N'}, "BFL", {0, -1, 'E'}},
    {"NorthFastRight", {0, 0, 'N'}, "BFR", {0, -1, 'W'}},
    {"WestMove", {0, 0, 'W'}, "BM", {1, 0, 'W'}},
    {"WestLeft", {0, 0, 'W'}, "BL", {0, 0, 'N'}},
    {"WestRight", {0, 0, 'W'}, "BR", {0, 0, 'S'}},
    {"WestFastMove", {0, 0, 'W'}, "BFM", {2, 0, 'W'}},
    {"WestFastLeft", {0, 0, 'W'}, "BFL", {1, 0, 'N'}},
    {"WestFastRight", {0, 0, 'W'}, "BFR", {1, 0, 'S'}},
    {"SouthMove", {0, 0, 'S'}, "BM", {0, 1, 'S'}},
    {"SouthLeft", {0, 0, 'S'}, "BL", {0, 0, 'W'}},
    {"SouthRight", {0, 0, 'S'}, "BR", {0, 0, 'E'}},
    {"SouthFastMove", {0, 0, 'S'}, "BFM", {0, 2, 'S'}},
    {"SouthFastLeft", {0, 0, 'S'}, "BFL", {0, 1, 'W'}},
    {"SouthFastRight", {0, 0, 'S'}, "BFR", {0, 1, 'E'}},
}};
}  // namespace

class ExecutorReverseCases : public testing::TestWithParam<ReverseCase>
{
};

TEST_P(ExecutorReverseCases, should_follow_reverse_movement_and_turn_rules)
{
    const ReverseCase& testCase = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor(testCase.initialPose));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute(testCase.commands);

    ASSERT_EQ(testCase.expectedPose, executor->Query());
}

INSTANTIATE_TEST_SUITE_P(
    FourHeadings, ExecutorReverseCases, testing::ValuesIn(reverseCases),
    [](const testing::TestParamInfo<ReverseCase>& information) { return std::string(information.param.name); });

TEST(ExecutorReverseTest, should_keep_pose_when_only_toggling_reverse)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("B");

    const Pose expected{2, 3, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorReverseTest, should_keep_reverse_state_between_execute_calls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("B");
    executor->Execute("M");

    const Pose expected{2, 2, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorReverseTest, should_cancel_reverse_after_second_B)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("BBM");

    const Pose expected{0, 1, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorReverseTest, should_move_forward_after_cancelling_reverse)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("BMBM");

    const Pose expected{0, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorReverseTest, should_keep_reverse_after_cancelling_fast)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("BFMFM");

    const Pose expected{-3, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorReverseTest, should_keep_fast_after_cancelling_reverse)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("BFMBM");

    const Pose expected{0, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorReverseTest, should_combine_fast_and_reverse_in_either_order)
{
    std::unique_ptr<Executor> first(Executor::NewExecutor({2, 3, 'E'}));
    std::unique_ptr<Executor> second(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, first.get());
    ASSERT_NE(nullptr, second.get());

    first->Execute("BFM");
    second->Execute("FBM");

    const Pose expected{0, 3, 'E'};
    ASSERT_EQ(expected, first->Query());
    ASSERT_EQ(expected, second->Query());
}

TEST(ExecutorReverseTest, should_keep_states_independent_between_executors)
{
    std::unique_ptr<Executor> first(Executor::NewExecutor({0, 0, 'E'}));
    std::unique_ptr<Executor> second(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, first.get());
    ASSERT_NE(nullptr, second.get());

    first->Execute("BFM");
    second->Execute("M");

    const Pose firstExpected{-2, 0, 'E'};
    const Pose secondExpected{1, 0, 'E'};
    ASSERT_EQ(firstExpected, first->Query());
    ASSERT_EQ(secondExpected, second->Query());
}

TEST(ExecutorReverseTest, should_execute_fast_reverse_actions_in_order)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("BFLMR");

    const Pose expected{-1, 3, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

}  // namespace adas
