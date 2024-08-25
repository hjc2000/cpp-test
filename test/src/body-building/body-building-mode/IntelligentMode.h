#pragma once
#include <base/IExecutable.h>
#include <base/math/ChXFilter.h>
#include <base/math/InertialElement.h>
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

    std::shared_ptr<base::ChXFilter> _filter{
        new base::ChXFilter{
            base::ChXFilter_KError{500},
            base::ChXFilter_FeedbackDiv{10000},
        },
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
