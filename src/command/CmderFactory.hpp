#pragma once

#include <functional>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "Command.hpp"

namespace adas
{
class CmderFactory final
{
public:
    using CommandHandler = std::function<ActionGroup(const PoseHandler&)>;

    CmderFactory() = default;
    CmderFactory(const CmderFactory&) = delete;
    CmderFactory& operator=(const CmderFactory&) = delete;

    std::vector<CommandHandler> GetCmders(std::string_view commands) const
    {
        std::vector<CommandHandler> result;

        for (std::string_view::size_type index = 0; index < commands.size(); ++index) {
            auto code = commands.substr(index, 2);
            if (code == "TR") {
                ++index;
            } else {
                code = commands.substr(index, 1);
            }

            const auto found = commandMap.find(code);
            if (found != commandMap.end()) {
                result.push_back(found->second);
            }
        }

        return result;
    }

private:
    const std::unordered_map<std::string_view, CommandHandler> commandMap{
        {"M", MoveCommand{}}, {"L", TurnLeftCommand{}}, {"R", TurnRightCommand{}},
        {"F", FastCommand{}}, {"B", ReverseCommand{}},  {"TR", TurnRoundCommand{}},
    };
};
}  // namespace adas