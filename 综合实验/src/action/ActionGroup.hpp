#pragma once

#include <initializer_list>
#include <vector>

namespace adas {

class PoseHandler;

enum class ActionType {
    ForwardOneStep,
    BackwardOneStep,
    TurnLeft,
    ReverseTurnLeft,
    TurnRight,
    ReverseTurnRight,
    ToggleFast,
    ToggleReverse
};

class ActionGroup final {
public:
    ActionGroup() = default;
    ActionGroup(std::initializer_list<ActionType> actions);
    void PushAction(ActionType action);
    void DoOperate(PoseHandler& poseHandler) const noexcept;
    const std::vector<ActionType>& GetActions() const noexcept;

private:
    std::vector<ActionType> actions;
};

}  // namespace adas
