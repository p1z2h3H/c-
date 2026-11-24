#pragma once

#include <initializer_list>
#include <vector>

#include "PoseHandler.hpp"

namespace adas
{
enum class ActionType {
    Forward,
    TurnLeft,
};

class ActionGroup
{
public:
    explicit ActionGroup(std::initializer_list<ActionType> actions) : actions{actions}
    {
    }

    void DoOperate(PoseHandler& state) const noexcept
    {
        for (const ActionType action : actions) {
            switch (action) {
            case ActionType::Forward:
                state.Forward();
                break;
            case ActionType::TurnLeft:
                state.TurnLeft();
                break;
            }
        }
    }

private:
    std::vector<ActionType> actions;
};
}  // namespace adas