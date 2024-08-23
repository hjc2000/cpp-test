#pragma once
#include <base/math/InertialElement.h>
#include <ChXFilter.h>
#include <Cmd.h>
#include <lua_api.h>
#include <memory>
#include <Option.h>
#include <Servo.h>
#include <TensionLinearInterpolator.h>

class BurnOutMode
{
private:
    BurnOutMode() = default;

public:
    static BurnOutMode &Instance()
    {
        static BurnOutMode o;
        return o;
    }

    void Execute();
};
