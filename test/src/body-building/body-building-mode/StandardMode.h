#pragma once
#include <base/IExecutable.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <memory>

/// @brief 信息获取器。其中的信息应该是实时更新的。
class IStandardMode_RequiredInformationGetter
{
public:
    virtual double Tension_kg() = 0;
    virtual double WindingSpeed_rpm() = 0;
    virtual double TorqueRatio() = 0;
};

class StandardMode :
    public base::IExecutable
{
private:
    std::shared_ptr<Cmd> _cmd;
    std::shared_ptr<IStandardMode_RequiredInformationGetter> _infos;
    std::shared_ptr<base::LinearInterpolator> _tension_linear_interpolator;
    double _current_tension_kg = 0;
    double _last_tension_kg = 0;

public:
    StandardMode(std::shared_ptr<Cmd> cmd,
                 std::shared_ptr<IStandardMode_RequiredInformationGetter> infos)
    {
        _cmd = cmd;
        _infos = infos;

        _current_tension_kg = _infos->Tension_kg();
        _last_tension_kg = _infos->Tension_kg();

        _tension_linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
            new base::LinearInterpolator{
                base::LinearInterpolator_StartVlaue{0},
                base::LinearInterpolator_EndVlaue{_infos->Tension_kg()},
                base::LinearInterpolator_StepLength{0.03},
            },
        };
    }

    void Execute();
};

void Test_StandardMode();
