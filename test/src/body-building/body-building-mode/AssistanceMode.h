#pragma once

class AssistanceMode
{
private:
    AssistanceMode() = default;

    int _unwinding_tick = 0;
    int _zlTim1 = 0;
    int _zlTim2 = 0;
    int _zlTimBase = 0;
    int _zlDistBase = 0;
    bool _has_effective_unwinding = false;
    bool _has_effective_winding = false;
    double _tension = 0;
    bool _zlSub = false;
    bool _zlTrigger = false;
    int _zlDist1 = 0;
    int _zlDist2 = 0;
    bool _needChk = false;

    void OnFromUnwindingToWinding();
    void OnFromWindingToUnwinding();
    double CalSubKg(double base_kg);

public:
    static AssistanceMode &Instance()
    {
        static AssistanceMode o;
        return o;
    }

    void Execute();
};
