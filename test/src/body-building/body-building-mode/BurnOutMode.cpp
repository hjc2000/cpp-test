#include "BurnOutMode.h"

void BurnOutMode::OnUnwindingTimesChanged()
{
    _end_point_line_length = _pull_times_detecter->TurningPoint();
    double pull_length = _end_point_line_length - _starting_point_line_length;
    if (_pull_times_detecter->UnwindingTimes() < 2)
    {
        // 被拉出次数小于 2
        _t2 = 0;
        _t3 = 0;
        _changing = false;
        _current_tension = _infos->Option_Tension_kg();
    }
    else if (_pull_times_detecter->UnwindingTimes() == 2)
    {
        _current_tension = _infos->Option_Tension_kg();
        _t2 = _current_tension * pull_length / _unwinding_tick;
        _last_pull_length = pull_length;
    }
    else if (_pull_times_detecter->UnwindingTimes() == 3)
    {
        _last_pull_length = (_last_pull_length + pull_length) / 2;
        _t3 = _current_tension * pull_length / _unwinding_tick;
        _power = (_t2 + _t3) / 2;
    }
    else
    {
        double ratio = pull_length / _last_pull_length;
        if (_changing)
        {
            ratio = 1;
        }

        double pt = 0;
        if (ratio < 0.7)
        {
            pt = _current_tension * pull_length / _unwinding_tick * ratio;
        }
        else
        {
            pt = _current_tension * pull_length / _unwinding_tick;
        }

        double pe_ratio = (pt - _power) / _power;
        double set_kg = _current_tension * 5 + 15;
        int chg_kg = (set_kg - 1) / 100;

        if (_changing)
        {
            _power = pt;
            _changing = false;
        }
        else
        {
            if (pe_ratio > 0.2 && pe_ratio < 0.5)
            {
                _current_tension = set_kg + chg_kg * 10 + 10;
                _changing = true;
            }
            else if (pe_ratio > 0.5)
            {
                _current_tension = set_kg + chg_kg * 10 + 20;
                _changing = true;
            }
            else if (pe_ratio < -0.2 && pe_ratio > -0.5)
            {
                _current_tension = set_kg - chg_kg * 10 - 10;
                _changing = true;
            }
            else if (pe_ratio < -0.5)
            {
                _current_tension = set_kg - chg_kg * 10 - 20;
                _changing = true;
            }
            else
            {
                _current_tension = set_kg;
            }

            if (_current_tension < 20)
            {
                _current_tension = 20;
            }
            else if (_current_tension > _infos->Option_MaxTension_kg())
            {
                _current_tension = _infos->Option_MaxTension_kg();
            }

            _current_tension = (_current_tension - 15) / 5;
        }
    }

    _tension_linear_interpolator->SetEndValue(_current_tension);
    _unwinding_tick = 0;
}

BurnOutMode::BurnOutMode(std::shared_ptr<Cmd> cmd,
                         std::shared_ptr<IBurnOutMode_InfomationGetter> infos)
{
    _cmd = cmd;
    _infos = infos;

    _tension_linear_interpolator->SetEndValue(_infos->Option_Tension_kg());
    _pull_times_detecter = std::shared_ptr<PullTimesDetector>{new PullTimesDetector{}};
    _current_tension = _infos->Option_Tension_kg();
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
    _last_tension = _current_tension;
    _current_tension = _infos->Option_Tension_kg();
    if (_last_pull_length != _current_tension)
    {
        _unwinding_tick = 0;
        _pull_times_detecter = std::shared_ptr<PullTimesDetector>{new PullTimesDetector{}};
    }

    _pull_times_detecter->Input(_infos->RleasedLengthOfLine());
    if (_infos->Servo_FeedbackSpeed() > 10)
    {
        _unwinding_tick++;
    }

    if (_pull_times_detecter->UnwindingTimesChanged())
    {
        OnUnwindingTimesChanged();
    }
    else if (_pull_times_detecter->WindingTimesChanged())
    {
        _starting_point_line_length = _pull_times_detecter->TurningPoint();
    }

    DD(8, (_current_tension * 5 + 15));
    double tension = ++(*_tension_linear_interpolator);
    double torque = tension * _infos->Option_TorqueRatio();
    _cmd->SetTorque(torque);
}
