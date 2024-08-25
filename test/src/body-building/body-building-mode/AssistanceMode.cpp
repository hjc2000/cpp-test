#include "AssistanceMode.h"

void AssistanceMode::Prepare()
{
    _pull_times_detecter.Input(_infos->RleasedLengthOfLine());
    if (_pull_times_detecter.UnwindingTimesChanged())
    {
        // 一次出绳已经完成，此时已经处在回绳的方向
        if (_pull_times_detecter.UnwindingTimes() < 2)
        {
        }
        else if (_pull_times_detecter.UnwindingTimes() == 2)
        {
            _reference_time = _unwinding_tick;
            _end_point_line_length = _pull_times_detecter.TurningPoint();
        }
        else if (_pull_times_detecter.UnwindingTimes() == 3)
        {
            _reference_time += _unwinding_tick;
            _reference_time = _reference_time / 2 + 500;

            _end_point_line_length += _pull_times_detecter.TurningPoint();
            _end_point_line_length = _end_point_line_length / 2 * 0.9;

            _pull_times_detecter.SetEffectiveUnwindingThreshold(_end_point_line_length);
            _pull_times_detecter.SetEffectiveWindingThreshold(_starting_point_line_length);
            _is_preparing = false;
        }

        _unwinding_tick = 0;
    }
    else if (_pull_times_detecter.WindingTimesChanged())
    {
        // 一次回绳已经完成，此时已经处在出绳的方向
        _starting_point_line_length = _pull_times_detecter.TurningPoint();
    }
}

double AssistanceMode::CalSubKg(double base_kg)
{
    double zlSubkg = (base_kg * 5 + 15) * 0.2;
    double zlSubkgV = static_cast<int>(zlSubkg / 5) * 5;
    if (zlSubkg - zlSubkgV > 0)
    {
        zlSubkgV = zlSubkgV + 5;
    }

    return zlSubkgV * 0.2;
}

AssistanceMode::AssistanceMode(std::shared_ptr<Cmd> cmd,
                               std::shared_ptr<IAssistanceMode_InfomationGetter> infos)
{
    _cmd = cmd;
    _infos = infos;

    _tension = _infos->Option_Tension_kg();

    _tension_linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
        new base::LinearInterpolator{
            base::LinearInterpolator_StartVlaue{0},
            base::LinearInterpolator_EndVlaue{_tension},
            base::LinearInterpolator_StepLength{0.03},
        },
    };
}

void AssistanceMode::Execute()
{
    _cmd->SetSpeed(_infos->Option_WindingSpeed_rpm());
    if (_infos->Servo_FeedbackSpeed() > 10)
    {
        _unwinding_tick++;
    }

    if (_is_preparing)
    {
        Prepare();
    }
    else
    {
        DD(14, _tension * 5 + 15);
        double torque = _tension * _infos->Option_TorqueRatio();
        _cmd->SetTorque(torque);
    }
}
