#pragma once
#include <base/IExecutable.h>
#include <base/math/DirectionDetecter.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <memory>
#include <Option.h>

class IAssistanceMode_InfomationGetter
{
public:
    virtual double Option_Tension_kg() = 0;
    virtual double Option_TorqueRatio() = 0;
    virtual double Option_WindingSpeed_rpm() = 0;
    virtual int Servo_FeedbackPosition() = 0;
    virtual double Servo_FeedbackSpeed() = 0;

    double RleasedLengthOfLine()
    {
        return Servo_FeedbackPosition() * 3.7 * 2 * 3.14 / 12000;
    }
};

class AssistanceMode :
    public base::IExecutable
{
private:
    int _unwinding_tick = 0;
    double _tension = 0;
    bool _has_effective_unwinding = false;
    bool _has_effective_winding = false;
    std::shared_ptr<Cmd> _cmd;
    std::shared_ptr<IAssistanceMode_InfomationGetter> _infos;
    std::shared_ptr<base::LinearInterpolator> _tension_linear_interpolator;

    std::shared_ptr<base::DirectionDetecter> _direction_detecter{
        new base::DirectionDetecter{
            base::DirectionDetecter_RisingThreshold{20},
            base::DirectionDetecter_FallenThreshold{-20},
            base::DirectionDetecter_Direction::Falling,
            0,
        },
    };

    void OnFromUnwindingToWinding();
    void OnFromWindingToUnwinding();
    double CalSubKg(double base_kg);

public:
    AssistanceMode(std::shared_ptr<Cmd> cmd,
                   std::shared_ptr<IAssistanceMode_InfomationGetter> infos)
    {
        _cmd = cmd;
        _infos = infos;

        _tension = _infos->Option_Tension_kg();

        _tension_linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
            new base::LinearInterpolator{
                base::LinearInterpolator_StartVlaue{0},
                base::LinearInterpolator_EndVlaue{_infos->Option_Tension_kg()},
                base::LinearInterpolator_StepLength{0.03},
            },
        };
    }

    void Execute() override;
};
