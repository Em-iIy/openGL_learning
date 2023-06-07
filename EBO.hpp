#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <GLAD/glad.h>
#include <vector>
#include <sys/types.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;

	EBO(void);
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	EBO(std::vector<uint> &indices);
	void Update(std::vector<uint> &indices);
	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif