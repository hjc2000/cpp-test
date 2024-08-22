#pragma once

class IntelligentMode
{
private:
    IntelligentMode() = default;

public:
    static IntelligentMode &Instance()
    {
        static IntelligentMode o;
        return o;
    }

    void Execute();
};
