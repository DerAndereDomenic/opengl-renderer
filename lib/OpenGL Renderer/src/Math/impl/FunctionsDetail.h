#ifndef __OPENGLRENDERER_MATH_IMPL_FUNCTIONSDETAIL_H
#define __OPENGLRENDERER_MATH_IMPL_FUNCTIONSDETAIL_H

template<typename T>
T
Math::lerp(T a, T b, float t)
{
	return a * (1.0f - t) + b * t;
}

template<typename T>
T
Math::smoothstep(T x)
{
	if (x <= 0) return 0;
	if (x >= 1) return 1;
	return 3.0f * x * x - 2.0f * x * x * x;
}

template<typename T>
T
Math::smoothlerp(T a, T b, T t)
{
	return a + smoothstep(t) * (b - a);
}

#endif