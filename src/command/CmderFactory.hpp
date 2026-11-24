#pragma once

#include <functional>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Command.hpp"

namespace adas {

using Cmder = std::function<ActionGroup(const PoseHandler&)>;
using CmderList = std::list<Cmder>;

class CmderFactory final {
public:
    CmderList GetCmders(const std::string& commands) const;

private:
    static std::string ParseCommandString(std::string_view commands);

    const std::unordered_map<char, Cmder> cmderMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()}, {'Z', TurnRoundCommand()}};
};

}  // namespace adas
