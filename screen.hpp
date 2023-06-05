#ifndef SCREEN_HPP
# define SCREEN_HPP

# define WIDTH 1000
# define HEIGHT 1000
# define DEPTH 1000
# define DISTANCE 1.5

#include <glm/vec3.hpp>

glm::vec3 toNDC(glm::vec3 px);
glm::vec3 toPX(glm::vec3 NDC);

#endif