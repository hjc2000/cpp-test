#pragma once
#include <base/IExecutable.h>
#include <base/math/InertialElement.h>
#include <base/math/LinearInterpolator.h>
#include <ChXFilter.h>
#include <Cmd.h>
#include <lua_api.h>
#include <memory>
#include <Option.h>

class IIntelligentMode_InfomationGetter
{
public:
    virtual double Option_Tension_kg() = 0;
    virtual double Option_WindingTorque() = 0;
    virtual double Option_WindingSpeed_rpm() = 0;
    virtual double Option_k() = 0;
    virtual double Option_b() = 0;
    virtual double Option_MaxTorque() = 0;
    virtual double Servo_FeedbackSpeed() = 0;
};

class IntelligentMode :
    public base::IExecutable
{
private:
    std::shared_ptr<Cmd> _cmd;
    std::shared_ptr<IIntelligentMode_InfomationGetter> _infos;
    base::InertialElement_TimeConstant const _little_time_constant{CalculateTimeConstant(5, 10000)};
    base::InertialElement_TimeConstant const _big_time_constant{CalculateTimeConstant(500, 10000)};

    std::shared_ptr<base::InertialElement> _filter{
        new base::InertialElement{
            _little_time_constant,
            base::InertialElement_SampleInterval{0.002},
        },
    };

    base::LinearInterpolator _tension_linear_interpolator{
        base::LinearInterpolator_StartVlaue{0},
        base::LinearInterpolator_EndVlaue{Option::Instance().Tension_kg()},
        base::LinearInterpolator_StepLength{0.03},
    };

    double CalculateTorque(double feedback_speed);

public:
    IntelligentMode(std::shared_ptr<Cmd> cmd,
                    std::shared_ptr<IIntelligentMode_InfomationGetter> infos)
    {
        _cmd = cmd;
        _infos = infos;
    }

    void Execute();
};
