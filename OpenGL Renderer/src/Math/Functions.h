#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <DataStructure/TUMPose.h>

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
	*	\brief Calculates the TUM pose from the view matrix
	*	\param[in] view The view matrix
	*	\return The TUM Pose
	*/
	TUMPose
	View2TUMPose(glm::mat4 view);
};

#include <Math/impl/FunctionsDetail.h>

#endif