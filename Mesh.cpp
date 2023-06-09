#include "Mesh.hpp"
#include <iostream>

void	Mesh::del(void)
{
	_VAO.Delete();
	_VBO.Delete();
	_EBO.Delete();
}

Mesh::Mesh(void)
{
	_VAO.Bind();
	_EBO = 
}

Mesh::~Mesh(void)
{
}

Mesh	&Mesh::operator=(Mesh const &rhs)
{
	(void)rhs;
	return (*this);
}

Mesh::Mesh(Mesh const &src)
{
	*this = src;
}
