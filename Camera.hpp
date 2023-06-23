#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glm/glm.hpp>
# include <glm/vec3.hpp>
# include <glm/mat4x4.hpp>
# include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW			= -90.0f;
const float	PITCH		= 0.0f;
const float	SPEED		= 2.5f;
const float	SENSITIVITY	= 0.03f;
const float	ZOOM		= 60.0f;

class Camera {
	private:
		void updateCameraVectors(void);
	
	public:
		// Camera attributes
		glm::vec3	Position;
		glm::vec3	WorldUp;
		glm::vec3	Front;
		glm::vec3	Right;
		glm::vec3	Up;

		// Euler angles
		float		Yaw;
		float		Pitch;

		// Camera options
		float		MovementSpeed;
		float		MouseSensitivity;
		float		Zoom;

		// View matrix getter
		glm::mat4	getViewMatrix(void) const;

		// Input processing
		void 	processKeyboard(Camera_Movement direction, float deltaTime);
		void	processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		void	processMouseScroll(float yoffset);

		// Constructor / Destructor
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		~Camera();
};

#endif