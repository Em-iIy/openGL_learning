#include "screen.hpp"


// -1 + 2 * (v3 / (screen space dimensions))
glm::vec3 toNDC(glm::vec3 px)
{
	return (-1.f + 2 * (px / glm::vec3(WIDTH, HEIGHT, DEPTH)));
}

glm::vec3 toPX(glm::vec3 NDC)
{
	return ()
}

