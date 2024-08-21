#pragma once

class State
{
private:
    double _released_length_of_line = 0;
    double _last_released_length_of_line = 0;

public:
    void Refresh_ReleasedLengthOfLine();
    double ReleasedLengthOfLine();
    double LastReleasedLengthOfLine();
    bool ReleasedLengthOfLineChanged();
};
