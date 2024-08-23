#pragma once
#include <base/math/InertialElement.h>
#include <memory>

std::shared_ptr<base::InertialElement> CreateInertialFilterFromChXFilter(int k_error, int feedback_div);

double CalculateTimeConstant(int k_error, int feedback_div);
