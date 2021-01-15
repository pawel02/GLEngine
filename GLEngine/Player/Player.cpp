#include "Player.h"

namespace
{
	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Player::get_camera().mouse_callback(xpos, ypos);
	}

	void mouse_scroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		Player::get_camera().mouse_scroll(xoffset, yoffset);
	}
}

Camera Player::camera { nullptr, 20.0f };

Player::Player(Window* window, Shader& shader) noexcept
	:window{ window }, g_window{ window->get_window() }
{
	camera.set_shader(&shader);

	//mouse input
	glfwSetCursorPosCallback(g_window, mouse_callback);
	glfwSetScrollCallback(g_window, mouse_scroll);
}

Player::~Player() noexcept
{
}

void Player::update(float deltaTime)
{
	
	if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(g_window, true);
	}

	//moving the camera around
	if (glfwGetKey(g_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.move_forward(deltaTime);
	}
	if (glfwGetKey(g_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.move_back(deltaTime);
	}
	if (glfwGetKey(g_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.move_left(deltaTime);
	}
	if (glfwGetKey(g_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.move_right(deltaTime);
	}
}
