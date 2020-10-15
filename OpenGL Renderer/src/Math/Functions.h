#ifndef __OPENGLRENDERER_MATH_FUNCTIONS_H
#define __OPENGLRENDERER_MATH_FUNCTIONS_H

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

	/**
	*	\brief A smoothstep function used for interpolation
	*	\param[in] x The interpolation parameter
	*	\return The smoothed interpolation parameter
	*	\note: See https://en.wikipedia.org/wiki/Smoothstep
	*/
	template<typename T>
	T smoothstep(T x);

	/**
	*	\brief A smooth linear interpolation
	*	\param[in] a The first value
	*	\param[in] b The second value
	*	\param[in] t The interpolation step
	*	\return The interpolated value
	*	\note: See https://en.wikipedia.org/wiki/Perlin_noise
	*/
	template<typename T>
	T smoothlerp(T a, T b, T t);
};

#include <Math/impl/FunctionsDetail.h>

#endif