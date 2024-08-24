#pragma once
#include <base/IExecutable.h>
#include <Cmd.h>
#include <memory>

class ModeSelector : public base::IExecutable
{
private:
    std::shared_ptr<base::IExecutable> _body_building_executable;
    std::shared_ptr<Cmd> _cmd;

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
