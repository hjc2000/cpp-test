#include "ConstantSpeedMode.h"
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

void ConstantSpeedMode::Execute()
{
}
