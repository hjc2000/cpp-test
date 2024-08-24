#include "StandardMode.h"
#include <Servo.h>
#include <thread>

void StandardMode::Execute()
{
    _cmd->SetSpeed(_infos->WindingSpeed_rpm());
    _current_tension_kg = _infos->Tension_kg();
    if (_last_tension_kg != _current_tension_kg)
    {
        _last_tension_kg = _current_tension_kg;
        _tension_linear_interpolator->SetEndValue(_current_tension_kg);
    }

    double tension = ++(*_tension_linear_interpolator);
    if (tension < 4)
    {
        tension = 4;
    }

    double torque = tension * _infos->TorqueRatio();
    _cmd->SetTorque(torque);
}

void Test_StandardMode()
{
    class Getter :
        public IStandardMode_RequiredInformationGetter
    {
    public:
        virtual double Tension_kg() override
        {
            return 5;
        }

        virtual double WindingSpeed_rpm() override
        {
            return 20;
        }

        virtual double TorqueRatio() override
        {
            return 1.85;
        }
    };

    std::shared_ptr<Cmd> cmd{new Cmd{}};
    std::shared_ptr<Getter> getter{new Getter{}};
    StandardMode mode{cmd, getter};
    for (int i = 0; i < 500; i++)
    {
        mode.Execute();
        std::cout << (*cmd) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds{10});
    }
}
