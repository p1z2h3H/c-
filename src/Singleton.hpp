#pragma once

namespace adas
{
template <typename T>
class Singleton final
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

private:
    Singleton() = delete;
};
}  // namespace adas