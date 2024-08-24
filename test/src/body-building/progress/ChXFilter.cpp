#include "ChXFilter.h"

std::shared_ptr<base::InertialElement> CreateInertialFilterFromChXFilter(int k_error, int feedback_div)
{
    return std::shared_ptr<base::InertialElement>{
        new base::InertialElement{
            base::InertialElement_TimeConstant{0.002 * feedback_div / k_error},
            base::InertialElement_SampleInterval{0.002},
        },
    };
}

double CalculateTimeConstant(int k_error, int feedback_div)
{
    return 0.002 * feedback_div / k_error;
}
