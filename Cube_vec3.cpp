#include "Cube_vec3.hpp"
#include <iostream>
#include <string.h>
#include <cstring>

static glm::vec3 v3_base_vertices[] = {
	glm::vec3(-1.0f, -1.0f, 1.0f), // bottom left front 	0
	glm::vec3(1.0f, -1.0f, 1.0f), // bottom right front 	1
	glm::vec3(-1.0f, 1.0f, 1.0f), // top left front 		2
	glm::vec3(1.0f, 1.0f, 1.0f), // top right front 		3
	glm::vec3(-1.0f, 1.0f, -1.0f), // top left back 		4
	glm::vec3(1.0f, 1.0f, -1.0f), // top right back 		5
	glm::vec3(-1.0f, -1.0f, -1.0f), // bottom left back	6
	glm::vec3(1.0f, -1.0f, -1.0f) // bottom right back		7
};

// cube
static GLuint mesh_indices[] = {
	1, 3, 2, 0, 1, 2,	// front
	4, 6, 0, 4,			// left
	5, 3, 2, 5,			// top
	7, 6, 4, 7,			// back
	1, 3, 5, 1,			// right
	0, 6, 7				// bottom
};

// static GLuint frame_indices[] = {
// 	4, 5, 6, 4, // back bottom triangle
// 	6, 7, 7, 5, // back top triangle
// 	6, 0, // left top triangle
// 	2, 4, // left bottom triangle
// 	7, 1, // right bottom triangle
// 	3, 5, // right top triangle
// 	0, 1, 2, 0, // front bottom triangle
// 	2, 3, 3, 1 // front top triangle
// };

void Cube::Delete(void)
{
	this->_VAO.Delete();
	this->_VBO.Delete();
	this->_EBO.Delete();
}

void	Cube::Clear(void)
{
	for (uint i = 0; i < sizeof(v3_base_vertices) / sizeof(glm::vec3); ++i)
		this->_draw_buffer[i] = v3_base_vertices[i];
}

void	Cube::Transform(glm::mat3 mat)
{
	std::vector<glm::vec3>::iterator it = _draw_buffer.begin();
	std::vector<glm::vec3>::iterator ite = _draw_buffer.end();
	while (it != ite)
	{
		*it = mat * *it;
		++it;
	}
}

void	Cube::Transform(glm::mat4 mat)
{
	glm::vec4 temp;
	std::vector<glm::vec3>::iterator it = _draw_buffer.begin();
	std::vector<glm::vec3>::iterator ite = _draw_buffer.end();
	while (it != ite)
	{
		*it = glm::vec3(mat * glm::vec4(*it, 1.0f));
		++it;
	}
}

// void	Cube::Rotate(float angle, glm::vec3 axis)
// {

// }

void	Cube::DrawMesh(GLfloat dist)
{
	std::vector<glm::vec3>::iterator it = _draw_buffer.begin();
	std::vector<glm::vec3>::iterator ite = _draw_buffer.end();
	while (it != ite)
	{
		*it *= _size;
		*it += _coords;
		float z = 1 / (dist - (*it).z);
		
		glm::mat3 projection(
			glm::vec3(z, 0, 0),
			glm::vec3(0, z, 0),
			glm::vec3(0, 0, 0)
		);
		*it = projection * *it;
		++it;
	}
	this->_VAO.Bind();
	this->_VBO.Update(this->_draw_buffer);
	glDrawElements(GL_LINE_STRIP, sizeof(mesh_indices), GL_UNSIGNED_INT, 0);
	this->_VAO.Unbind();
}
void	Cube::DrawFrame(GLfloat dist)
{
	// std::vector<glm::vec3>::iterator it = _draw_buffer.begin();
	// std::vector<glm::vec3>::iterator ite = _draw_buffer.end();
	// while (it != ite)
	// {
	// 	float z = 1 / (dist - (*it).z);
		
	// 	glm::mat3 projection(
	// 		glm::vec3(z, 0, 0),
	// 		glm::vec3(0, z, 0),
	// 		glm::vec3(0, 0, 0)
	// 	);
	// 	*it = projection * *it;
	// 	++it;
	// }
	this->_VAO.Bind();
	this->_VBO.Update(this->_draw_buffer);
	glDrawElements(GL_LINES, sizeof(mesh_indices), GL_UNSIGNED_INT, 0);
	this->_VAO.Unbind();

}

void	Cube::setCoord(glm::vec3 coord)
{
	this->_coords = coord;
}

glm::vec3	Cube::getCoord(void) const
{
	return (this->_coords);
}

Cube::Cube(glm::vec3 coords, GLfloat size): _coords(coords), _size(size)
{
	this->_draw_buffer.resize(sizeof(v3_base_vertices) / sizeof(glm::vec3));
	// _size = 0;
	this->Clear();
	this->_VAO.Bind();
	this->_VBO = VBO(this->_draw_buffer);
	this->_EBO = EBO(mesh_indices, sizeof(mesh_indices));
	this->_VAO.LinkAtr(this->_VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
	this->_VAO.Unbind();
	this->_VBO.Unbind();
	this->_EBO.Unbind();
}

Cube::~Cube()
{
}

// Cube	&Cube::operator=(Cube const &rhs)
// {
// 	(void)rhs;
// 	return (*this);
// }

// Cube::Cube(Cube const &src)
// {
// 	*this = src;
// }
