#pragma once

#include "action/ActionGroup.hpp"

namespace adas {

class PoseHandler;

class MoveCommand final {
public:
    ActionGroup operator()(const PoseHandler& state) const;
};

class TurnLeftCommand final {
public:
    ActionGroup operator()(const PoseHandler& state) const;
};

class TurnRightCommand final {
public:
    ActionGroup operator()(const PoseHandler& state) const;
};

class FastCommand final {
public:
    ActionGroup operator()(const PoseHandler& state) const;
};

class ReverseCommand final {
public:
    ActionGroup operator()(const PoseHandler& state) const;
};

class TurnRoundCommand final {
public:
    ActionGroup operator()(const PoseHandler& state) const;
};

}  // namespace adas
