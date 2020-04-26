#ifndef MATH_IMPL_FUNCTIONSDETAIL_H
#define MATH_IMPL_FUNCTIONSDETAIL_H

template<typename T>
T
Math::lerp(T a, T b, float t)
{
	return a * (1.0f - t) + b * t;
}

#endif