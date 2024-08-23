#pragma once
#include <base/math/InertialElement.h>
#include <ChXFilter.h>
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

    base::InertialElement_TimeConstant const _little_time_constant{CalculateTimeConstant(5, 10000)};
    base::InertialElement_TimeConstant const _big_time_constant{CalculateTimeConstant(500, 10000)};

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
