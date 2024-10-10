#include <base/di/SingletonGetter.h>
#include <iostream>

namespace
{
    class Int
    {
    public:
        Int(int num)
        {
            _num = num;
        }

        int _num = 0;
    };

    class Getter :
        public base::SingletonGetter<Int>
    {
    protected:
        std::unique_ptr<Int> Create() override
        {
            return std::unique_ptr<Int>{new Int{777}};
        }

        void Lock() override
        {
        }

        void Unlock() override
        {
        }
    };
} // namespace

int F2()
{
    Getter o;
    std::cout << &o.Instance() << std::endl;
    return o.Instance()._num;
}
