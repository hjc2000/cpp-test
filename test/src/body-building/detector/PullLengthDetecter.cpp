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
        _max_length = 0;
    }

    if (_has_effective_unwinding &&
        DirectionDetector::Instance().DirectionChange() == DirectionDetector_DirectionChange::FromUnwindingToWinding)
    {
        // 经历了有效出绳，且现在方向从出绳变成收绳了
        _has_effective_unwinding = false;

        // 方向切换瞬间的绳长就是本轮拉绳的最大长度
        _max_length = DirectionDetector::Instance().ReleasedLengthOfLineWhenDirectionChanged();
    }
    else if (_has_effective_winding &&
             DirectionDetector::Instance().DirectionChange() == DirectionDetector_DirectionChange::FromWindingToUnwinding)
    {
        // 经历了有效收线，现在方向变成放线了
        _has_effective_winding = false;
        _min_length = DirectionDetector::Instance().ReleasedLengthOfLineWhenDirectionChanged();
    }
}
