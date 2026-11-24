#pragma once

#include "Direction.hpp"
#include "Executor.hpp"
#include "Point.hpp"

namespace adas {

class PoseHandler final {
public:
    explicit PoseHandler(const Pose& pose, VehicleType type = VehicleType::Normal) noexcept;
    void Forward() noexcept;
    void Backward() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    void Reverse() noexcept;
    bool IsFast() const noexcept;
    bool IsReverse() const noexcept;
    VehicleType GetVehicleType() const noexcept;
    Pose Query() const noexcept;

private:
    Point point;
    Direction facing;
    VehicleType type;
    bool fast{false};
    bool reverse{false};
};

}  // namespace adas
