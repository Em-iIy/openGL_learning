#include "Cube.hpp"
#include <iostream>
#include <string.h>

void Cube::loadMesh(const char *filename)
{
	std::string content;
	try
	{
		content = readFile(filename);
	}
	catch(const std::exception& e)
	{
		std::cerr << filename << ": " << e.what() << '\n';
	}
	size_t vertIdx = content.find("vertices{");
	if (vertIdx == std::string::npos)
		throw (std::runtime_error("parse error: cube: couldn't find vertices"));
	vertIdx += strlen("vertices{\n");
	while (true)
	{
		vertIdx = content.find_first_of("-.f1234567890}", vertIdx);
		if (content[vertIdx == '}'])
			break ;
		this->_base_vertices.push_back(std::atof(&content[vertIdx]) * this->_size);
		vertIdx = content.find_first_not_of("-.f1234567890", vertIdx);
	}
	size_t indIdx = content.find("indices{");
	if (indIdx == std::string::npos)
		throw (std::runtime_error("parse error: cube: couldn't find indices"));
	indIdx += strlen("indices{\n");
	while (true)
	{
		indIdx = content.find_first_of("-.f1234567890}", indIdx);
		if (content[indIdx] == '}')
			break ;
		this->_base_indices.push_back(std::atof(&content[indIdx]));
		indIdx = content.find_first_not_of("-.f1234567890", indIdx);
	}
}

void Cube::Delete(void)
{
	this->_VAO.Delete();
	this->_VBO.Delete();
	this->_EBO.Delete();
	delete [] this->_indices;
	delete [] this->_vertices;
}

Cube::Cube(GLfloat coords[3], GLfloat size): _size(size)
{
	try
	{
		this->loadMesh("resources/objects/cube.mesh");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit (EXIT_FAILURE);
	}
	for (uint i = 0; i < 3; ++i)
		this->_coords[i] = coords[i];
	this->_vertices = new GLfloat[this->_base_vertices.size()];
	this->_indices = new GLuint[this->_base_indices.size()];
	this->_VAO.Bind();
	this->_VBO = VBO(this->_vertices, this->_base_vertices.size() * sizeof(GLfloat));
	this->_EBO = EBO(this->_indices, this->_base_indices.size() * sizeof(GLuint));
	this->_VAO.LinkAtr(this->_VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
	this->_VAO.Unbind();
	this->_VBO.Unbind();
	this->_EBO.Unbind();
}

Cube::~Cube(void)
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
