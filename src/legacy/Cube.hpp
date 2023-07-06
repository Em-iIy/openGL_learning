#ifndef CUBE_HPP
# define CUBE_HPP

#include <GLAD/glad.h>
#include <glm/vec3.hpp>
#include <vector>
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "readFile.hpp"

enum {
	CUBE_FRAME,
	CUBE_MESH,
	CUBE_TRIANGLE
};

class Cube
{
	private:
		VAO			_VAO;
		VBO			_VBO;
		EBO			_EBO;
		glm::vec3	_coords;
		GLfloat		_size;
		GLfloat		*_draw_buffer;

	public:
		void	Delete(void);
		// Resets draw buffer to base vertices
		void	Clear(void);
		// Transforms draw buffer with passed matrix
		void	Transform(GLfloat mat[3][3]);
		// Draws the cube as a mesh
		void	DrawMesh(GLfloat dist);
		// Draws the cube as it's frame
		void	DrawFrame(GLfloat dist);
	
		Cube(glm::vec3 coords, GLfloat size);
		~Cube();
		// Cube(Cube const &src);
		// Cube	&operator=(Cube const &rhs);
};

#endif
