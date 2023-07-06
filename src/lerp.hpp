#ifndef LERP_HPP
# define LERP_HPP

#include <cmath>

template <typename T>
T lerp(T x, T y, float t)
{
	return (x * (1.f - t) + y * t);
}

template <typename T>
T quadratic_lerp(T p0, T p1, T p2, float t)
{
	return (lerp(lerp(p0, p1, t), lerp(p1, p2, t), t));
}

template <typename T>
T cubic_lerp(T p0, T p1, T p2, T p3, float t)
{
	const float diff = 1 - t;

	// return (lerp(quadratic_lerp(p0, p1, p2, t), quadratic_lerp(p1, p2, p3, t), t));
	return (
		powf(diff, 3) * p0 +
		3 * powf(diff, 2) * t * p1 +
		3 * (diff) * powf(t, 2) * p2 +
		powf(t, 3) * p3
	);
}

template <typename T>
T cubic_lerp_derivitive1(T p0, T p1, T p2, T p3, float t)
{
	const float diff = 1 - t;

	return (
		3 * powf(diff, 2) * (p1 - p0) +
		6 * diff * t * (p2 - p1) +
		3 * powf(t, 2) * (p3 - p2)
	);
}

#endif