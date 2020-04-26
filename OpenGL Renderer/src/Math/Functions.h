#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

namespace Math
{
	template<typename T>
	T lerp(T a, T b, float t);
};

#include <Math/impl/FunctionsDetail.h>

#endif