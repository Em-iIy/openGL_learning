#ifndef SCREEN_HPP
# define SCREEN_HPP

# define WIDTH 1000
# define HEIGHT 1000
# define DEPTH 1000
# define DISTANCE 1.5

#include <glm/vec3.hpp>

template <typename T>
T toNDC(T px, size_t size)
{
	return (px / size * 2 - 1);
}


#endif