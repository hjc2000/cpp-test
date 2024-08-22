#pragma once

class ModeSelector
{
private:
    ModeSelector() = default;

    void HandleAfterBodyBuildingMode();
    void SelectOneBodyBuildingModeToExecute();
    void SelectOneModeToExecute();

public:
    static ModeSelector &Instance()
    {
        static ModeSelector o;
        return o;
    }

    void Execute();
};
