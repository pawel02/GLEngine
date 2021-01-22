#include "Player.h"

#include "../Events/Event.h"

Player::Player(Window* window, Shader& shader) noexcept
	:window{ window }, g_window{ window->get_window() }, camera{ nullptr, 20.0f }
{
	camera.set_shader(&shader);


	MouseMovedEvent::subscribe([&](double xpos, double ypos) {
		get_camera().mouse_callback(xpos, ypos);
	});

	//mouse input
	MouseScolledEvent::subscribe([&](double xpos, double ypos) {
			get_camera().mouse_scroll(xpos, ypos);
		});
}

Player::~Player() noexcept
{
}

void Player::update(float deltaTime)
{
	camera.update();
	
	if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(g_window, true);
	}
	
	if (glfwGetKey(g_window, GLFW_KEY_Q) == GLFW_RELEASE)
	{
		if (isKeyDown)
		{
			if (!isWireframe)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			isWireframe = !isWireframe;
		}

		isKeyDown = false;
	}

	if (glfwGetKey(g_window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		isKeyDown = true;
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
