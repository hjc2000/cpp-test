#include "CalibrateZeroPointMode.h"
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>

void CalibrateZeroPointMode::Execute()
{
}

bool CalibrateZeroPointMode::IsCompleted() const
{
    return _is_completed;
}
