#include "Curve.hpp"
#include "lerp.hpp"
#include <iostream>
#include <string.h>
#include <cstring>

std::ostream &operator<<(std::ostream &o, glm::vec3 &v);


void Curve::Delete(void)
{
	this->_VAO.Delete();
	this->_VBO.Delete();
	this->_EBO.Delete();
}

void	Curve::Draw(void)
{
	// std::cout << _a << " " << _b << std::endl;
	this->_VAO.Bind();
	this->_VBO.Update(this->_draw_buffer);
	glDrawElements(GL_LINES, (this->_indices.size() - 1) * sizeof(uint), GL_UNSIGNED_INT, 0);
	// glDrawElements(GL_POINTS, this->_indices.size() * sizeof(uint), GL_UNSIGNED_INT, 0);
	this->_VAO.Unbind();
}

glm::vec3 Curve::getPos(float t) const
{
	return (cubic_lerp(_a, _control1, _control2, _b, t));
}

Curve::Curve(uint steps, glm::vec3 a, glm::vec3 control1, glm::vec3 control2, glm::vec3 b): _a(a), _control1(control1), _control2(control2), _b(b)
{
	float step_size = 1.f / steps;
	uint idx = 0;
	for (float i = 0.f; i <= 1.0001f; i += step_size)
	{
		this->_draw_buffer.push_back(cubic_lerp(a, control1, control2, b, i));
		// std::cout << this->_draw_buffer[idx] << std::endl;
		this->_indices.push_back(idx);
		this->_indices.push_back(idx + 1);
		++idx;
	}
	this->_indices.pop_back();
	this->_VAO.Bind();
	this->_VBO = VBO(this->_draw_buffer);
	this->_EBO = EBO(this->_indices.data(), (this->_indices.size() - 1) * sizeof(uint));
	this->_VAO.LinkAtr(this->_VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
	this->_VAO.Unbind();
	this->_VBO.Unbind();
	this->_EBO.Unbind();
}

Curve::~Curve()
{
}

// Curve	&Curve::operator=(Curve const &rhs)
// {
// 	(void)rhs;
// 	return (*this);
// }

// Curve::Curve(Curve const &src)
// {
// 	*this = src;
// }
