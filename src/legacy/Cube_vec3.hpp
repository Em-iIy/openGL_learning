#ifndef CUBE_HPP_VEC3
# define CUBE_HPP_VEC3

#include <GLAD/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "utils/readFile.hpp"

enum {
	CUBE_FRAME,
	CUBE_MESH,
	CUBE_TRIANGLE
};

class Cube
{
	private:
		VAO						_VAO;
		VBO						_VBO;
		EBO						_EBO;
		glm::vec3				_coords;
		GLfloat					_size;
		std::vector<glm::vec3>	_draw_buffer;

	public:
		void	Delete(void);
		// Resets draw buffer to base vertices
		void	Clear(void);
		// Transforms draw buffer with passed matrix
		void	Transform(glm::mat3 mat);
		void	Transform(glm::mat4 mat);
		// Draws the cube as a mesh
		void	DrawMesh(GLfloat dist);
		// Draws the cube as it's frame
		void	DrawFrame(GLfloat dist);

		void	setCoord(glm::vec3 coord);
		glm::vec3	getCoord(void) const;

		Cube(glm::vec3 coords, GLfloat size);
		~Cube();
		// Cube(Cube const &src);
		// Cube	&operator=(Cube const &rhs);
};

#endif
