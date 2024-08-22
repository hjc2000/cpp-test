#include "TensionLinearInterpolator.h"
#include <Option.h>

void TensionLinearInterpolator::ChangeEndValue(double value)
{
    if (_linear_interpolator != nullptr)
    {
        _linear_interpolator = nullptr;
        _current_output = value;
        return;
    }

    if (value > _current_output)
    {
        double kg = static_cast<double>(_current_output) / 2 + 1.5;
        if (kg < 15)
        {
            _linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
                new base::LinearInterpolator{
                    static_cast<double>(_current_output),
                    static_cast<double>(value),
                    base::LinearInterpolator_StepCount{1000},
                },
            };
        }
        else if (kg < 25)
        {
            _linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
                new base::LinearInterpolator{
                    static_cast<double>(_current_output),
                    static_cast<double>(value),
                    base::LinearInterpolator_StepCount{1500},
                },
            };
        }
        else
        {
            _linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
                new base::LinearInterpolator{
                    static_cast<double>(_current_output),
                    static_cast<double>(value),
                    base::LinearInterpolator_StepCount{2500},
                },
            };
        }
    }
    else
    {
        double dif = static_cast<double>(_current_output - value) / 2;
        if (dif < 15)
        {
            _linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
                new base::LinearInterpolator{
                    static_cast<double>(_current_output),
                    static_cast<double>(value),
                    base::LinearInterpolator_StepCount{500},
                },
            };
        }
        else
        {
            _linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
                new base::LinearInterpolator{
                    static_cast<double>(_current_output),
                    static_cast<double>(value),
                    base::LinearInterpolator_StepCount{1000},
                },
            };
        }
    }
}

double TensionLinearInterpolator::StepForward()
{
    if (_linear_interpolator != nullptr)
    {
        (*_linear_interpolator)++;
    }

    return CurrentOutput();
}

double TensionLinearInterpolator::CurrentOutput()
{
    if (_linear_interpolator != nullptr)
    {
        _current_output = _linear_interpolator->CurrentValue();
    }

    if (_current_output < 4)
    {
        _current_output = 4;
    }

    return _current_output;
}
