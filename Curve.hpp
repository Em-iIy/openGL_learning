#ifndef CURVE_HPP
# define CURVE_HPP

#include <GLAD/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "readFile.hpp"

class Curve
{
	private:
		VAO						_VAO;
		VBO						_VBO;
		EBO						_EBO;
		std::vector<glm::vec3>	_draw_buffer;
		std::vector<uint>		_indices;

	public:
		void	Delete(void);

		void	Draw(void);

		Curve(uint steps, glm::vec3 a, glm::vec3 control1, glm::vec3 control2, glm::vec3 b);
		~Curve();
		// Curve(Curve const &src);
		// Curve	&operator=(Curve const &rhs);
};

#endif
