#include "PullLengthDetecter.h"
#include <PullTimesDetector.h>
#include <State.h>

void PullLengthDetecter::Execute()
{
    _direction_detecter.Input(State::Instance().ReleasedLengthOfLine());
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
        _direction_detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromRisingToFalling)
    {
        // 经历了有效出绳，且现在方向从出绳变成收绳了
        _has_effective_unwinding = false;

        // 方向切换瞬间的绳长就是本轮拉绳的最大长度
        _pull_length = _direction_detecter.TurningPoint() - _starting_point;
    }
    else if (_has_effective_winding &&
             _direction_detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromFallingToRising)
    {
        // 经历了有效收线，现在方向变成放线了
        _has_effective_winding = false;
        _starting_point = _direction_detecter.TurningPoint();
        _last_pull_length = _pull_length;
        _pull_length = 0;
    }
}
