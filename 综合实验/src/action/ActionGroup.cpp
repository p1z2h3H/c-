#include "ActionGroup.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>

#include "Action.hpp"

namespace adas {

ActionGroup::ActionGroup(std::initializer_list<ActionType> actions) : actions(actions) {}

void ActionGroup::PushAction(ActionType action)
{
    actions.push_back(action);
}

void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept
{
    using Action = std::function<void(PoseHandler&)>;
    static const std::array<Action, 8> operations{
        ForwardAction(), BackwardAction(), TurnLeftAction(), ReverseTurnLeftAction(),
        TurnRightAction(), ReverseTurnRightAction(), FastAction(), ReverseAction()};

    std::for_each(actions.begin(), actions.end(), [&poseHandler](ActionType action) {
        operations[static_cast<std::size_t>(action)](poseHandler);
    });
}

const std::vector<ActionType>& ActionGroup::GetActions() const noexcept
{
    return actions;
}

}  // namespace adas
