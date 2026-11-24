#pragma once

#include "core/PoseHandler.hpp"

namespace adas {

class ForwardAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.Forward(); }
};

class BackwardAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.Backward(); }
};

class TurnLeftAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.TurnLeft(); }
};

class ReverseTurnLeftAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.TurnRight(); }
};

class TurnRightAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.TurnRight(); }
};

class ReverseTurnRightAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.TurnLeft(); }
};

class FastAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.Fast(); }
};

class ReverseAction final {
public:
    void operator()(PoseHandler& state) const noexcept { state.Reverse(); }
};

}  // namespace adas
