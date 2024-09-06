#include <base/di/CreateInstance.h>
#include <base/di/GetInstance.h>
#include <base/di/GetSingletonInstance.h>
#include <base/di/SingletonGetter.h>
#include <iostream>

class IntSingletonGetter :
    public base::SingletonGetter<int>
{
public:
    std::unique_ptr<int> Create() override
    {
        return std::unique_ptr<int>{new int{666}};
    }

    void Lock() override
    {
        std::cout << "加锁" << std::endl;
    }

    void Unlock() override
    {
        std::cout << "解锁" << std::endl;
    }
};

namespace base
{
    template <>
    int &GetSingletonInstance<int>()
    {
        IntSingletonGetter getter;
        return getter.Instance();
    }

    template <>
    std::shared_ptr<int> CreateInstance<int>()
    {
        return std::shared_ptr<int>{new int{777}};
    }

    template <>
    std::shared_ptr<int> GetInstance<int>()
    {
        return std::shared_ptr<int>{new int{888}};
    }
} // namespace base
