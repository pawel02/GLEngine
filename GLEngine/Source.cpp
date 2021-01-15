#include "window/Window.h"

#include <iostream>

#include "./Renderer/Renderer.h"
#include "./textures/Texture2D.h"

#include "Camera/Camera.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;


Camera camera{nullptr, 2.5f};

void process_input(GLFWwindow* window, float deltaTime);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


int main()
{
	//initialize glfw
	if (!glfwInit())
	{
		std::cout << "Could not initialize glfw\n";
		return -1;
	}

	Window window{ std::move(Vector2<unsigned int>{800, 600}), "GLEngine", false };

	//mouse input
	glfwSetCursorPosCallback(window.get_window(), mouse_callback);
	glfwSetScrollCallback(window.get_window(), scroll_callback);


	//vertecies
	//const float vertecies[] = {
	//	 0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      1.0f, 1.0f,// top right
	//	 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f,// bottom right
	//	-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f,// bottom left
	//	-0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,      0.0f, 1.0f,// top left 
	//};
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	const unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	VertexBuffer VBO{ sizeof(vertices), vertices };

	//IndexBuffer EBO{ sizeof(indices), indices };

	//vao is useful because all of the buffers get bound to it so when it comes
	//to drawing you only need to bind the vao instead of all the buffers individually
	VertexArray VAO{ GL_FLOAT };
	VAO.add_layout_element({ 3, GL_FALSE });
	//VAO.add_layout_element({ 3, GL_FALSE });
	VAO.add_layout_element({ 2, GL_FALSE });
	VAO.compile_layout();


	//load all of the necessary shaders
	Shader shader{ "../../GLEngine/GLEngine/shaders/vertex.vert", "../../GLEngine/GLEngine/shaders/fragment.frag" };
	shader.bind();

	//add all the textures
	Texture2D texture{ &shader };
	float border[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	texture.add_texture("../../GLEngine/GLEngine/res/brick.jpg", "ourTexture");
	texture.add_texture("../../GLEngine/GLEngine/res/wood.jpg", "ourTexture2");

	texture.bind_all();

	Renderer renderer;

	//camera
	camera = Camera{ &shader, 20.0f };

	glm::vec3 cubePos[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::mat4 model{ 1.0f };
	//main loop
	while (!window.is_open())
	{
		renderer.clear();

		process_input(window.get_window(), window.get_delta_time());

		window.update();

		//move the camera around
		camera.update();

		//move all the models around a little
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePos[i]);

			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
				glm::vec3(0.5f, 1.0f, 0.0f));
			shader.set_uniform_mat4("model", model);

			renderer.draw(VBO, VAO, shader);
		}

		window.after_update();
	}

	//cleanup
	glfwTerminate();

	return 0;
}


void process_input(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//moving the camera around
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.move_forward(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.move_back(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.move_left(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.move_right(deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.mouse_callback(xpos, ypos);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.mouse_scroll(xoffset, yoffset);
}