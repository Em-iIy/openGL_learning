#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>

std::ostream &operator<<(std::ostream &o, glm::vec3 &v);
std::ostream &operator<<(std::ostream &o, glm::vec4 &v);