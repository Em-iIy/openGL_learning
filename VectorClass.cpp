#include "VectorClass.hpp"
#include <iostream>
#include <algorithm>

std::ostream &operator<<(std::ostream &o, glm::vec3 &v);

void 	VectorClass::Delete(void)
{
	this->_VAO.Delete();
	this->_VBO.Delete();
	this->_EBO.Delete();
}

void	VectorClass::Clear(void)
{
	this->_vertices.clear();
	this->_indices.clear();
}

void	VectorClass::Draw(void)
{
	for (auto it = _indices.begin(); it != _indices.end(); ++it)
	{
		// if (*it == _vertices.size())
			std::cout << *it << std::endl;
	}
	for (auto it = _vertices.begin(); it != _vertices.end(); ++it)
	{
		// if (*it == _vertices.size())
			std::cout << *it << std::endl;
	}
	this->_VAO.Bind();
	this->_VBO.Update(this->_vertices);
	this->_EBO.Update(this->_indices);
	glDrawElements(GL_LINES, this->_indices.size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_POINTS, 0, this->_vertices.size());
	this->_VAO.Unbind();
	this->_VBO.Unbind();
	this->_EBO.Unbind();
}

void	VectorClass::AddVector(glm::vec3 origin, glm::vec3 vect)
{
	uint i;
	// std::cout << "Adding: " << origin << " to: " << vect << std::endl; 
	for (i = 0; i < this->_vertices.size(); ++i)
	{
		if (this->_vertices[i] == origin)
		{
			this->_indices.push_back(i);
			break ;
		}
	}
	if (i == this->_vertices.size())
	{
		// this->_indices.push_back(this->_vertices.size());
		this->_vertices.push_back(origin);
		this->_indices.push_back(i);
	}
	for (i = 0; i < this->_vertices.size(); ++i)
	{
		if (this->_vertices[i] == vect)
		{
			this->_indices.push_back(i);
			break ;
		}
	}
	if (i == this->_vertices.size())
	{
		// this->_indices.push_back(this->_vertices.size());
		this->_vertices.push_back(vect);
		this->_indices.push_back(i);
	}
}

size_t	VectorClass::size(void) const
{
	return (this->_vertices.size());
}

VectorClass::VectorClass(void)
{
	this->_VAO.Bind();
	this->_VBO = VBO(this->_vertices);
	this->_EBO = EBO(this->_indices);
	this->_VAO.LinkAtr(this->_VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
	this->_VAO.Unbind();
	this->_VBO.Unbind();
	this->_EBO.Unbind();
}

VectorClass::~VectorClass()
{
}
