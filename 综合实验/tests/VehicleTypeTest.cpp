#include <gtest/gtest.h>

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas {
namespace {

struct MotionCase {
    VehicleType type;
    std::string commands;
    Pose initial;
    Pose expected;
    std::string name;
};

struct StateExpectations {
    VehicleType type;
    const char* typeName;
    const char* prefix;
    const char* stateName;
    std::array<Pose, 3> outcomes;
};

Pose RotateFromEast(Pose pose, unsigned initialDirection)
{
    const std::string headings = "NESW";
    const auto finalDirection = headings.find(pose.heading);
    const auto x = pose.x;
    const auto y = pose.y;
    switch (initialDirection) {
    case 0: pose.x = -y; pose.y = x; break;
    case 1: break;
    case 2: pose.x = y; pose.y = -x; break;
    case 3: pose.x = -x; pose.y = -y; break;
    }
    pose.heading = headings[(finalDirection + initialDirection + 3) % 4];
    pose.x += 3;
    pose.y -= 5;
    return pose;
}

std::vector<MotionCase> BuildMotionCases()
{
    const std::array<StateExpectations, 12> rows{{
        {VehicleType::Normal, "Normal", "", "Normal", {{{1, 0, 'E'}, {0, 0, 'N'}, {0, 0, 'S'}}}},
        {VehicleType::Normal, "Normal", "F", "Fast", {{{2, 0, 'E'}, {1, 0, 'N'}, {1, 0, 'S'}}}},
        {VehicleType::Normal, "Normal", "B", "Reverse", {{{-1, 0, 'E'}, {0, 0, 'S'}, {0, 0, 'N'}}}},
        {VehicleType::Normal, "Normal", "BF", "FastReverse", {{{-2, 0, 'E'}, {-1, 0, 'S'}, {-1, 0, 'N'}}}},
        {VehicleType::Sport, "Sport", "", "Normal", {{{2, 0, 'E'}, {0, 1, 'N'}, {0, -1, 'S'}}}},
        {VehicleType::Sport, "Sport", "F", "Fast", {{{4, 0, 'E'}, {1, 1, 'N'}, {1, -1, 'S'}}}},
        {VehicleType::Sport, "Sport", "B", "Reverse", {{{-2, 0, 'E'}, {0, 1, 'S'}, {0, -1, 'N'}}}},
        {VehicleType::Sport, "Sport", "BF", "FastReverse", {{{-4, 0, 'E'}, {-1, 1, 'S'}, {-1, -1, 'N'}}}},
        {VehicleType::Bus, "Bus", "", "Normal", {{{1, 0, 'E'}, {1, 0, 'N'}, {1, 0, 'S'}}}},
        {VehicleType::Bus, "Bus", "F", "Fast", {{{2, 0, 'E'}, {2, 0, 'N'}, {2, 0, 'S'}}}},
        {VehicleType::Bus, "Bus", "B", "Reverse", {{{-1, 0, 'E'}, {-1, 0, 'S'}, {-1, 0, 'N'}}}},
        {VehicleType::Bus, "Bus", "BF", "FastReverse", {{{-2, 0, 'E'}, {-2, 0, 'S'}, {-2, 0, 'N'}}}}
    }};
    const std::string commands = "MLR";
    const std::string headings = "NESW";
    std::vector<MotionCase> cases;
    for (const auto& row : rows) {
        for (unsigned command = 0; command < commands.size(); ++command) {
            for (unsigned heading = 0; heading < headings.size(); ++heading) {
                cases.push_back({row.type, std::string(row.prefix) + commands[command],
                                 {3, -5, headings[heading]}, RotateFromEast(row.outcomes[command], heading),
                                 std::string(row.typeName) + row.stateName + commands[command] + headings[heading]});
            }
        }
    }
    return cases;
}

class VehicleTypeTest : public testing::TestWithParam<MotionCase> {};

TEST_P(VehicleTypeTest, should_follow_vehicle_and_state_motion_rules)
{
    const auto& test = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor(test.initial, test.type));
    ASSERT_NE(nullptr, executor.get());
    executor->Execute(test.commands);
    EXPECT_EQ(test.expected, executor->Query());
}

INSTANTIATE_TEST_SUITE_P(AllVehiclesStatesAndDirections, VehicleTypeTest,
                        testing::ValuesIn(BuildMotionCases()),
                        [](const testing::TestParamInfo<MotionCase>& info) { return info.param.name; });

}  // namespace
}  // namespace adas
