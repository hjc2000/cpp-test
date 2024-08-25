#include "AssistanceMode.h"

double AssistanceMode::CalSubKg(double base_kg)
{
    double zlSubkg = (base_kg * 5 + 15) * 0.2;
    double zlSubkgV = static_cast<int>(zlSubkg / 5) * 5;
    if (zlSubkg - zlSubkgV > 0)
    {
        zlSubkgV = zlSubkgV + 5;
    }

    return zlSubkgV * 0.2;
}

void AssistanceMode::Execute()
{
    _cmd->SetSpeed(_infos->Option_WindingSpeed_rpm());
    if (_infos->Servo_FeedbackSpeed() > 10)
    {
        _unwinding_tick++;
    }

    _pull_times_detecter.Input(_infos->RleasedLengthOfLine());
    if (_pull_times_detecter.UnwindingTimesChanged())
    {
    }
    else if (_pull_times_detecter.WindingTimesChanged())
    {
    }

    DD(14, _tension * 5 + 15);
    double torque = _tension * _infos->Option_TorqueRatio();
    _cmd->SetTorque(torque);
}
