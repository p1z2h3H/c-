#pragma once
#include <cstdint>
#include <string>

namespace adas
{
struct Pose {
    std::int32_t x;
    std::int32_t y;
    char heading;
};
enum class VehicleType { Normal, Sport, Bus };
class Executor
{
public:
    static Executor* NewExecutor(
        const Pose& pose = {0, 0, 'N'}, VehicleType type = VehicleType::Normal) noexcept;

    Executor() = default;
    virtual ~Executor() = default;

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    virtual void Execute(const std::string& commands) noexcept = 0;
    virtual Pose Query() const noexcept = 0;
};
}  // namespace adas
