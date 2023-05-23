#include "Cube.hpp"
#include <iostream>

Cube::Cube(GLfloat x, GLfloat y, GLfloat z): _coords({x, y, z})
{
	
}

Cube::~Cube(void)
{
}

Cube	&Cube::operator=(Cube const &rhs)
{
	(void)rhs;
	return (*this);
}

Cube::Cube(Cube const &src)
{
	*this = src;
}
