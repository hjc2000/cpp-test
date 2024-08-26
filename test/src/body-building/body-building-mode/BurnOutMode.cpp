#include "BurnOutMode.h"

void BurnOutMode::Prepare()
{
    _tension_linear_interpolator->SetEndValue(_current_option_tension);
    if (_pull_times_detecter->UnwindingTimesChanged())
    {
        if (_pull_times_detecter->UnwindingTimes() == 2)
        {
            _end_point_line_length = _pull_times_detecter->TurningPoint();

            double pull_length = _end_point_line_length - _starting_point_line_length;
            _reference_power = _current_option_tension * pull_length / _unwinding_tick;
        }
        else if (_pull_times_detecter->UnwindingTimes() == 3)
        {
            _end_point_line_length += _pull_times_detecter->TurningPoint();
            _end_point_line_length = _end_point_line_length / 2;

            double pull_length = _end_point_line_length - _starting_point_line_length;
            _reference_power += _current_option_tension * pull_length / _unwinding_tick;
            _reference_power = _reference_power / 2;
        }

        _unwinding_tick = 0;
    }
    else if (_pull_times_detecter->WindingTimesChanged())
    {
        _starting_point_line_length = _pull_times_detecter->TurningPoint();
    }
}

void BurnOutMode::Work()
{
}

BurnOutMode::BurnOutMode(std::shared_ptr<Cmd> cmd,
                         std::shared_ptr<IBurnOutMode_InfomationGetter> infos)
{
    _cmd = cmd;
    _infos = infos;

    _tension_linear_interpolator->SetEndValue(_infos->Option_Tension_kg());
    _pull_times_detecter = std::shared_ptr<PullTimesDetector>{new PullTimesDetector{}};

    _current_option_tension = _infos->Option_Tension_kg();
    _adjusted_tension = _current_option_tension;

    _tension_linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
        new base::LinearInterpolator{
            base::LinearInterpolator_StartVlaue{0},
            base::LinearInterpolator_EndVlaue{_infos->Option_Tension_kg()},
            base::LinearInterpolator_StepLength{0.03},
        },
    };
}

void BurnOutMode::Execute()
{
    _cmd->SetSpeed(_infos->Option_WindingSpeed_rpm());
    _current_option_tension = _infos->Option_Tension_kg();
    if (_infos->Servo_FeedbackSpeed() > 10)
    {
        _unwinding_tick++;
    }

    _pull_times_detecter->Input(_infos->RleasedLengthOfLine());
    if (_is_preparing)
    {
        Prepare();
    }
    else
    {
        Work();
    }

    DD(8, (_current_option_tension * 5 + 15));
    double tension = ++(*_tension_linear_interpolator);
    double torque = tension * _infos->Option_TorqueRatio();
    _cmd->SetTorque(torque);
}
