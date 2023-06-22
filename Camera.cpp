#include "Camera.hpp"
#include <iostream>

Camera::~Camera(void)
{
}

void	Camera::updateCameraVectors(void)
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::cross(Right, Front);
}

glm::mat4	Camera::getViewMatrix(void) const
{
	return (glm::lookAt(Position, Position + Front, Up));
}

void	Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
	case FORWARD:
		Position += Front * velocity;
		break ;
	case BACKWARD:
		Position -= Front * velocity;
		break ;
	case LEFT:
		Position -= Right * velocity;
		break ;
	case RIGHT:
		Position += Right * velocity;
		break ;
	case UP:
		Position += WorldUp * velocity;
		break ;
	case DOWN:
		Position -= WorldUp * velocity;
		break ;
	default:
		break;
	}
}

void	Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		else if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void	Camera::processMouseScroll(float yoffset)
{
	Zoom -= yoffset;
	if (Zoom > 90.0f)
		Zoom = 90.0f;
	else if (Zoom < 1.0f)
		Zoom = 1.0f;
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
