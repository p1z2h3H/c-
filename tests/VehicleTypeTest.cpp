#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
TEST(VehicleTypeTest, should_follow_motion_rules_for_sport_and_bus)
{
    const struct {
        VehicleType type;
        const char* prefix;
        Pose expected[3];
    } cases[] = {
        {VehicleType::Sport, "", {{0, 2, 'N'}, {-1, 0, 'W'}, {1, 0, 'E'}}},
        {VehicleType::Sport, "F", {{0, 4, 'N'}, {-1, 1, 'W'}, {1, 1, 'E'}}},
        {VehicleType::Sport, "B", {{0, -2, 'N'}, {-1, 0, 'E'}, {1, 0, 'W'}}},
        {VehicleType::Sport, "BF", {{0, -4, 'N'}, {-1, -1, 'E'}, {1, -1, 'W'}}},
        {VehicleType::Bus, "", {{0, 1, 'N'}, {0, 1, 'W'}, {0, 1, 'E'}}},
        {VehicleType::Bus, "F", {{0, 2, 'N'}, {0, 2, 'W'}, {0, 2, 'E'}}},
        {VehicleType::Bus, "B", {{0, -1, 'N'}, {0, -1, 'E'}, {0, -1, 'W'}}},
        {VehicleType::Bus, "BF", {{0, -2, 'N'}, {0, -2, 'E'}, {0, -2, 'W'}}},
    };
    const char operations[] = {'M', 'L', 'R'};

    for (const auto& testCase : cases) {
        for (int index = 0; index < 3; ++index) {
            const auto commands = std::string(testCase.prefix) + operations[index];
            SCOPED_TRACE(::testing::Message() << (testCase.type == VehicleType::Sport ? "Sport " : "Bus ") << commands);

            std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, testCase.type));
            ASSERT_NE(nullptr, executor.get());

            executor->Execute(commands);

            EXPECT_EQ(testCase.expected[index], executor->Query());
        }
    }
}
}  // namespace adas