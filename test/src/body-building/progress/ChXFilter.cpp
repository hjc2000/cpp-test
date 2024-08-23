#include "ChXFilter.h"

std::shared_ptr<base::InertialElement> CreateInertialFilterFromChXFilter(int k_error, int feedback_div)
{
    /* 		k_error = (T * k) / T1
     *	 	k_error = T * (k / T1)
     * 		k_error = 0.002 * (k / T1)
     *
     * 则
     * 		k / T1 = k_error / 0.002
     * 		T1 / k = 0.002 / k_error
     *
     * 惯性时间常数为
     *		T1 / (k * kb)
     * 		= (T1 / k) / kb
     * 		= (T1 / k) * feedback_div
     * 		= 0.002 / k_error * feedback_div
     */
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
