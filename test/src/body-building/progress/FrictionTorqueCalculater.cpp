#include "FrictionTorqueCalculater.h"
#include <cmath>
#include <Option.h>
#include <Servo.h>

int FrictionTorqueCalculater::WindingFrictionTorque() const
{
    return 4 * Option::Instance().TorqueRatio();
}

int FrictionTorqueCalculater::UnwindingFrictionTorque(double tension_kg) const
{
    double outFcRatio = 15;
    double outFcSet = 0.4;
    return (outFcSet - (tension_kg / outFcRatio)) * Option::Instance().TorqueRatio();
}

int FrictionTorqueCalculater::Calculate(double tension_kg)
{
    double mcl = 2;
    int torque = 0;
    if (Servo::Instance().FeedbackSpeed() >= 0 && Servo::Instance().FeedbackSpeed() < mcl)
    {
        // 低速放线
        double base = UnwindingFrictionTorque(tension_kg);
        double ratio = std::abs(Servo::Instance().FeedbackSpeed()) / mcl;
        torque = base * ratio;
    }
    else if (Servo::Instance().FeedbackSpeed() < 0 && Servo::Instance().FeedbackSpeed() > -mcl)
    {
        // 低速收线
        double base = WindingFrictionTorque();
        double ratio = std::abs(Servo::Instance().FeedbackSpeed()) / mcl;
        torque = base * ratio;
    }
    else if (Servo::Instance().FeedbackSpeed() > mcl)
    {
        // 高速放线
        torque = UnwindingFrictionTorque(tension_kg);
    }
    else
    {
        // 高速收线
        torque = WindingFrictionTorque();
    }

    torque = static_cast<int>(_filter.Input(torque));
    return torque;
}
