#pragma once

class AssistanceMode
{
private:
    AssistanceMode() = default;

    int _unwinding_tick = 0;
    bool _has_effective_unwinding = false;
    bool _has_effective_winding = false;
    double _tension = 0;

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
