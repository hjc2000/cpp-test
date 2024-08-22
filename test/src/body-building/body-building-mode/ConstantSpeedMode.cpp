#include "ConstantSpeedMode.h"
#include <cmath>
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>
#include <TensionLinearInterpolator.h>

double ConstantSpeedMode::TorqueGrowRatio()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            return SRV_PARA(1, 39) / 1000;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            return 1;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            return 1.45;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            return 2;
        }
    default:
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            return 0.6;
        }
    }
}

double ConstantSpeedMode::SpeedLimit()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            return SRV_PARA(1, 21) / 100;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            return 1400;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            return 1100;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            return 1;
        }
    default:
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            return 1800;
        }
    }
}

int ConstantSpeedMode::Torque()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            return SRV_PARA(2, 18);
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            return 13;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            return 30;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            return 45;
        }
    default:
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            return 6;
        }
    }
}

double ConstantSpeedMode::WindingSpeed()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            return SRV_PARA(1, 10) / 100;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            return 600;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            return 400;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            return 300;
        }
    default:
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            return 800;
        }
    }
}

int ConstantSpeedMode::FilterGain()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            return SRV_PARA(1, 20);
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            return 200;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            return 200;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            return 1000;
        }
    default:
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            return 500;
        }
    }
}

std::shared_ptr<base::InertialElement> ConstantSpeedMode::CreateFilter()
{
    return CreateInertialFilterFromChXFilter(FilterGain(), 10000);
}

void ConstantSpeedMode::Execute()
{
    if (Option::Instance().BodyBuildingModeChanged() || Option::Instance().Tension_kg_Changed())
    {
        _filter = CreateFilter();
    }

    double torque = 0;
    if (Servo::Instance().FeedbackSpeed() > DD(11))
    {
        torque = Servo::Instance().FeedbackSpeed() * TorqueGrowRatio();
        if (torque > SpeedLimit())
        {
            torque = SpeedLimit();
        }

        torque = std::pow(torque, 4) * std::pow(SpeedLimit(), 4);
        if (torque < 5)
        {
            torque = 5;
        }
        else if (torque > 180)
        {
            torque = 180;
        }

        Cmd::Instance().SetSpeed(0);
    }
    else
    {
        torque = Torque();
        Cmd::Instance().SetSpeed(WindingSpeed());
    }

    torque = _filter->Input(torque);
    if (torque < 5)
    {
        torque = 5;
    }
    else if (torque > 150)
    {
        torque = 150;
    }

    Cmd::Instance().SetTorque(torque);
}
