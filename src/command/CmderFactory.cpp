#include "CmderFactory.hpp"

namespace adas {

std::string CmderFactory::ParseCommandString(std::string_view commands)
{
    std::string result;
    result.reserve(commands.size());
    for (std::string_view::size_type position = 0; position < commands.size(); ++position) {
        const char command = commands[position];
        if (command == 'T' && position + 1 < commands.size() && commands[position + 1] == 'R') {
            result.push_back('Z');
            ++position;
        } else if (command != 'Z') {
            result.push_back(command);
        }
    }
    return result;
}

CmderList CmderFactory::GetCmders(const std::string& commands) const
{
    CmderList cmders;
    for (const char command : ParseCommandString(commands)) {
        const auto found = cmderMap.find(command);
        if (found != cmderMap.end()) {
            cmders.push_back(found->second);
        }
    }
    return cmders;
}

}  // namespace adas
