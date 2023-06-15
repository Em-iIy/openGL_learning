#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GLAD/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

struct Vertex {
	glm::vec3	pos;
	glm::vec3	color;
	glm::vec2	texUV;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;

	VBO(void);
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex> &vertices);

	VBO(std::vector<glm::vec3> &vertices);
	void Update(std::vector<glm::vec3> &vertices);

	VBO(GLfloat* vertices, GLsizeiptr size);
	void Update(GLfloat *vertices, GLsizeiptr size);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif