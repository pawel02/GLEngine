#include "Window.h"
#include <iostream>

#include "../Events/Event.h"

//making sure that this does no leak to other files
namespace
{
	void frame_buffer_resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}

Window::Window(Vector2<unsigned int>&& size, const char* name, bool show_mouse) noexcept
	:size{ std::move(size) }
{
	//initialize glfw
	if (!glfwInit())
	{
		std::cout << "Could not initialize glfw\n";
	}


	//this is mainly for if you are on a MAC
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.5);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	//MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(size.x, size.y, name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	make_current();

	//turn on vsync
	glfwSwapInterval(1);


	if (!show_mouse)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD \n";
	}

	glEnable(GL_MULTISAMPLE);
	glViewport(0, 0, size.x, size.y);
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetFramebufferSizeCallback(window, frame_buffer_resize);

	//subscribe to all events
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		{
			MouseMovedEvent::OnEvent(xpos, ypos);
		});
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		MouseScolledEvent::OnEvent(xpos, ypos);
		});
}

Window::~Window() noexcept
{
}

void Window::make_current()
{
	glfwMakeContextCurrent(window);
}

bool Window::is_open()
{
	return glfwWindowShouldClose(window);
}

void Window::update()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Window::after_update()
{
	//moves the back buffer to the front (Double buffering)
	glfwSwapBuffers(window);

	//poll for any events
	glfwPollEvents();
}

