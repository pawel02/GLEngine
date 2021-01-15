#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/Shader.h"

class Camera
{
private:
	//you are a little back at the start from the world origin
	glm::vec3 cameraPos{ 0.0f, 0.0f, 3.0f };
	//always look 1 unit infront of the camera
	glm::vec3 cameraFront{ 0.0f, 0.0f, -1.0f };
	//default up vector
	glm::vec3 cameraUp{ 0.0f, 1.0f, 0.0f };

	//I am using the perspective projection later ortho will be also added as an option
	glm::mat4 projection{1.0f};

	Shader* shader;

	float speed;

	glm::mat4 view;

	//camera mouse input
	float firstMouse = true;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0f;
	float lastY = 600.0f / 2.0f;
	float fov = 45.0f;
public:

	explicit Camera(Shader* shader, float speed) noexcept;
	//just for testing get rid off this later
	Camera(const Camera& other) noexcept
		:shader{ other.shader }, speed{ other.speed }, view{other.view},
		cameraFront{other.cameraFront}, cameraPos{other.cameraPos}, cameraUp{other.cameraUp}
	{}

	~Camera() noexcept;

	void set_speed(float new_speed);

	//movement
	void move_forward(float deltaTime);
	void move_back(float deltaTime);
	void move_right(float deltaTime);
	void move_left(float deltaTime);

	//mouse input
	void mouse_callback(float xpos, float ypos);
	void mouse_scroll(double xoffset, double yoffset);

	void set_fov(float new_fov) { fov = new_fov; }

	void set_shader(Shader* shader);
	void update();
};