#pragma once

class AssistanceMode
{
private:
    AssistanceMode() = default;

public:
    static AssistanceMode &Instance()
    {
        static AssistanceMode o;
        return o;
    }

    void Execute();
};
