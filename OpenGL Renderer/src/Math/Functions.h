#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

namespace Math
{
	/**
	*	\brief Interpolates between a and b
	*	\tparam T The type
	*	\param[in] a The first value
	*	\param[in] b The second value
	*	\param[in] t The interpolation step
	*	\return a(1-t)+tb
	*/
	template<typename T>
	T lerp(T a, T b, float t);
};

#include <Math/impl/FunctionsDetail.h>

#endif