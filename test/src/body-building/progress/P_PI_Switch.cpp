#include "P_PI_Switch.h"
#include <Option.h>
#include <Servo.h>

void P_PI_Switch::Execute()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::Standard:
        {
            if (Servo::Instance().FeedbackPosition() < Option::Instance().ZeroPositionProtectionThreshold())
            {
                Servo::Instance().Use_PI_Control();
            }
            else
            {
                Servo::Instance().Use_P_Control();
            }

            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode1:
    case Option_BodyBuildingMode::ConstantSpeedMode2:
    case Option_BodyBuildingMode::ConstantSpeedMode3:
    case Option_BodyBuildingMode::ConstantSpeedMode4:
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            // TODO:看一下 DD11 是什么
            /*
                if (Servo_FeedbackSpeed_rpm() < DD(11)) then
                    Servo_Use_PI_Control()
                else
                    Servo_Use_P_Control()
                end
            */

            break;
        }
    default:
        {
            Servo::Instance().Use_PI_Control();
            break;
        }
    }
}
