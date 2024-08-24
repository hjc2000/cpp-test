#include "SpringMode.h"
#include <Cmd.h>
#include <format>
#include <thread>

void SpringMode::Execute()
{
    _cmd->SetSpeed(_infos->Option_WindingSpeed_rpm());
    _current_tension_kg = _infos->Option_Tension_kg();
    int feedback_position = _infos->Servo_FeedbackPosition();

    if (_last_tension_kg != _current_tension_kg)
    {
        _tension_linear_interpolator->SetEndValue(_current_tension_kg);

        _filter = std::shared_ptr<base::ChXFilter>{
            new base::ChXFilter{
                base::ChXFilter_KError{10},
                base::ChXFilter_FeedbackDiv{40},
            },
        };
    }

    double tension = ++(*_tension_linear_interpolator);
    double torque = tension * _infos->Option_TorqueRatio();

    if (feedback_position < _infos->Option_OneMeterPosition())
    {
        torque = torque * feedback_position / _infos->Option_OneMeterPosition();
        std::cout << std::format("1m 内，当前位置：{}", feedback_position) << std::endl;
    }
    else
    {
        int delta_position = feedback_position - _infos->Option_OneMeterPosition();

        // 每转一圈转矩增大  _infos->Option_SpringRatio()
        torque = torque + (delta_position * _infos->Option_SpringRatio() / 30000);
        std::cout << std::format("1m 外，当前位置：{}", feedback_position) << std::endl;
    }

    torque = _filter->Input(torque);
    if (torque < 5)
    {
        torque = 5;
    }

    _cmd->SetTorque(torque);
}

void Test_SpringMode()
{
    class Getter :
        public ISpringMode_InfomationGetter
    {
    public:
        virtual double Option_Tension_kg() override
        {
            return 10;
        }

        virtual double Option_TorqueRatio() override
        {
            return 1.85;
        }

        virtual double Option_WindingSpeed_rpm() override
        {
            return 50;
        }

        virtual int Option_OneMeterPosition() override
        {
            return 30000;
        }

        /// @brief 弹簧劲度系数。每转一圈转矩要增大的百分比。
        /// @return
        virtual double Option_SpringRatio() override
        {
            return 10;
        }

        int _feedback_position = 0;
        bool _is_rising = true;

        virtual int Servo_FeedbackPosition() override
        {
            if (_feedback_position >= 1000 * 100)
            {
                _is_rising = false;
            }
            else if (_feedback_position < 1000)
            {
                _is_rising = true;
            }

            if (_is_rising)
            {
                _feedback_position += 1000;
            }
            else
            {
                _feedback_position -= 1000;
            }

            return _feedback_position;
        }
    };

    std::shared_ptr<Cmd> cmd{new Cmd{}};
    std::shared_ptr<Getter> getter{new Getter{}};
    SpringMode mode{cmd, getter};
    for (int i = 0; i < 500; i++)
    {
        mode.Execute();
        std::cout << (*cmd) << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds{10});
    }
}
