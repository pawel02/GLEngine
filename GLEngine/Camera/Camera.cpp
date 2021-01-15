#include "Camera.h"

Camera::Camera(Shader* shader, float speed) noexcept
	:shader{shader}, speed {speed}, view{1.0f}
{
	projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
	//projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -4.0f, 4.0f);
	if(shader != nullptr)
		shader->set_uniform_mat4("projection", projection);
}

Camera::~Camera() noexcept
{
}

void Camera::set_speed(float new_speed)
{
	speed = new_speed;
}

void Camera::move_forward(float deltaTime)
{
	cameraPos += speed * cameraFront * deltaTime;
}

void Camera::move_back(float deltaTime)
{
	cameraPos -= speed * cameraFront * deltaTime;
}

void Camera::move_right(float deltaTime)
{
	//gets the camera right vector
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * deltaTime;
}

void Camera::move_left(float deltaTime)
{
	//gets the camera right vector and then negates it to move left
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * deltaTime;
}

void Camera::mouse_callback(float xpos, float ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void Camera::mouse_scroll(double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;

	//update the fov
	projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
	if (shader != nullptr)
		shader->set_uniform_mat4("projection", projection);
}

void Camera::set_shader(Shader* shader)
{
	this->shader = shader;
	shader->set_uniform_mat4("view", view);
	shader->set_uniform_mat4("projection", projection);
}

void Camera::update()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader->set_uniform_mat4("view", view);
}
