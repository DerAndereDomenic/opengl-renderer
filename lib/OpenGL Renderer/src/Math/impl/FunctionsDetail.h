#ifndef __OPENGLRENDERER_MATH_IMPL_FUNCTIONSDETAIL_H
#define __OPENGLRENDERER_MATH_IMPL_FUNCTIONSDETAIL_H

template<typename T>
T
Math::lerp(const T& a, const T& b, const float& t)
{
	return a * (1.0f - t) + b * t;
}

template<typename T>
T
Math::smoothstep(const T& x)
{
	if (x <= 0) return 0;
	if (x >= 1) return 1;
	return 3.0f * x * x - 2.0f * x * x * x;
}

template<typename T>
T
Math::smoothlerp(const T& a, const T& b, const T& t)
{
	return a + smoothstep(t) * (b - a);
}

#endif