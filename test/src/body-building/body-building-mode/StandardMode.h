#pragma once
#include <base/IExecutable.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <memory>

/// @brief 信息获取器。其中的信息应该是实时更新的。
class IStandardMode_InformationGetter
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
    std::shared_ptr<IStandardMode_InformationGetter> _infos;
    std::shared_ptr<base::LinearInterpolator> _tension_linear_interpolator;
    double _current_tension_kg = 0;
    double _last_tension_kg = 0;

public:
    StandardMode(std::shared_ptr<Cmd> cmd,
                 std::shared_ptr<IStandardMode_InformationGetter> infos);

    void Execute();
};

void Test_StandardMode();
