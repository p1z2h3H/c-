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
}  // namespace adas