#include "DirectionDetector.h"
#include <State.h>

void DirectionDetector::Execute()
{
    _detecter.Input(State::Instance().ReleasedLengthOfLine());
}
