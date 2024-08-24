#include "PullLengthDetecter.h"
#include <DirectionDetector.h>
#include <PullTimesDetector.h>

void PullLengthDetecter::Execute()
{
    if (PullTimesDetector::Instance().UnwindingTimesChanged())
    {
        // 经历了有效出绳
        _has_effective_unwinding = true;
    }
    else if (PullTimesDetector::Instance().WindingTimesChanged())
    {
        // 经历了有效收绳
        _has_effective_winding = true;
    }

    if (_has_effective_unwinding &&
        DI_DirectionDetecter().DirectionChange() == base::DirectionDetecter_DirectionChange::FromRisingToFalling)
    {
        // 经历了有效出绳，且现在方向从出绳变成收绳了
        _has_effective_unwinding = false;

        // 方向切换瞬间的绳长就是本轮拉绳的最大长度
        _pull_length = DI_DirectionDetecter().TurningPoint() - _starting_point;
    }
    else if (_has_effective_winding &&
             DI_DirectionDetecter().DirectionChange() == base::DirectionDetecter_DirectionChange::FromFallingToRising)
    {
        // 经历了有效收线，现在方向变成放线了
        _has_effective_winding = false;
        _starting_point = DI_DirectionDetecter().TurningPoint();
        _last_pull_length = _pull_length;
        _pull_length = 0;
    }
}
