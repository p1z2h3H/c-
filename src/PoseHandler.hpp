#pragma once
#include "Direction.hpp"
#include "Executor.hpp"
#include "Point.hpp"
namespace adas
{
class PoseHandler
{
public:
    explicit PoseHandler(const Pose& initialPose) noexcept;
    Pose Query() const noexcept;
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;
    void Reverse() noexcept;

private:
    Point point;
    Direction direction;
    bool fast{false};
    bool reverse{false};
};
}  // namespace adas