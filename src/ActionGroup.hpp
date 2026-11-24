#pragma once

#include <initializer_list>
#include <vector>

#include "PoseHandler.hpp"

namespace adas
{
enum class ActionType {
    Forward,
    Backward,
    TurnLeft,
    TurnRight,
    ReverseTurnLeft,
    ReverseTurnRight,
    ToggleFast,
    ToggleReverse,
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
            case ActionType::Backward:
                state.Backward();
                break;
            case ActionType::TurnLeft:
            case ActionType::ReverseTurnRight:
                state.TurnLeft();
                break;
            case ActionType::TurnRight:
            case ActionType::ReverseTurnLeft:
                state.TurnRight();
                break;
            case ActionType::ToggleFast:
                state.Fast();
                break;
            case ActionType::ToggleReverse:
                state.Reverse();
                break;
            }
        }
    }

private:
    std::vector<ActionType> actions;
};
}  // namespace adas