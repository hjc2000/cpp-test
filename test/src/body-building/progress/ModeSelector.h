#pragma once
#include <base/IExecutable.h>
#include <memory>

class ModeSelector : public base::IExecutable
{
private:
    std::shared_ptr<base::IExecutable> _body_building_executable;

    void HandleAfterBodyBuildingMode();
    void CreateBodyBuildingModeExecutable();

public:
    static ModeSelector &Instance()
    {
        static ModeSelector o;
        return o;
    }

    void Execute();
};
