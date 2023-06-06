#ifndef SCREEN_HPP
# define SCREEN_HPP

# define WIDTH 2000
# define HEIGHT 2000
# define DEPTH 2000
# define DISTANCE 1.5

#include <glm/vec3.hpp>

template <typename T>
T toNDC(T px, size_t size)
{
	return (px / size * 2 - 1);
}


#endif