#include "PullTimesDetector.h"
#include <State.h>

void PullTimesDetector::Execute()
{
    _hysteresis_element.Input(State::Instance().ReleasedLengthOfLine());
    if (_hysteresis_element.OutputChange() == base::HysteresisElement_OutputChange::Rise)
    {
        _unwinding_times++;
    }
    else if (_hysteresis_element.OutputChange() == base::HysteresisElement_OutputChange::Fall)
    {
        _winding_times++;
    }

    if (State::Instance().ReleasedLengthOfLine() - State::Instance().LastReleasedLengthOfLine() > 0)
    {
        // 当前是放线方向
        if (State::Instance().ReleasedLengthOfLine() > _hysteresis_element.RisingThreshold())
        {
            /* 出绳距离超过上升阈值，将迟滞特性曲线右移，使得上升阈值与当前位置相等，
             * 使得回绳时不用回到原本的下降阈值处。
             */
            _hysteresis_element.MoveX(State::Instance().ReleasedLengthOfLine() - _hysteresis_element.RisingThreshold());
        }
    }
    else
    {
        // 当前在收绳阶段
        if (State::Instance().ReleasedLengthOfLine() < _hysteresis_element.FallenThreshold())
        {
            // 回绳后位置小于下降阈值，将迟滞特性曲线左移
            _hysteresis_element.MoveX(State::Instance().ReleasedLengthOfLine() - _hysteresis_element.FallenThreshold());
        }
    }
}

bool PullTimesDetector::WindingTimesChanged() const
{
    return _hysteresis_element.OutputChange() == base::HysteresisElement_OutputChange::Fall;
}

bool PullTimesDetector::UnwindingTimesChanged() const
{
    return _hysteresis_element.OutputChange() == base::HysteresisElement_OutputChange::Rise;
}
