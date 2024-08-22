#pragma once
#include <base/math/InertialElement.h>
#include <lua_api.h>
#include <memory>

class IntelligentMode
{
private:
    IntelligentMode() = default;

    double k()
    {
        return SRV_PARA(1, 45) / 100;
    }

    double b()
    {
        return SRV_PARA(1, 46) / 100;
    }

    /// @brief 先随便定的，暂时不知道为什么要一个大惯性时间常数，一个小惯性时间常数。
    base::InertialElement_TimeConstant const _little_time_constant{0.025};
    base::InertialElement_TimeConstant const _big_time_constant{_little_time_constant.Value() * 500};

    std::shared_ptr<base::InertialElement> _filter{
        new base::InertialElement{
            _little_time_constant,
            base::InertialElement_SampleInterval{0.002},
        },
    };

public:
    static IntelligentMode &Instance()
    {
        static IntelligentMode o;
        return o;
    }

    void Execute();
};
