#pragma once
#include "Direction.hpp"
#include "Executor.hpp"
#include "Point.hpp"
namespace adas
{
class PoseHandler
{
public:
    explicit PoseHandler(const Pose& initialPose, VehicleType type = VehicleType::Normal) noexcept;
    VehicleType GetVehicleType() const noexcept
    {
        return vehicleType;
    }
    Pose Query() const noexcept;
    void Forward() noexcept;
    void Backward() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;
    void Reverse() noexcept;
    bool IsReverse() const noexcept;

private:
    Point point;
    Direction direction;
    VehicleType vehicleType;
    bool fast{false};
    bool reverse{false};
};
}  // namespace adas