#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "./Renderer/Renderer.h"
#include "Texture2D.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	//initialize glfw
	if (!glfwInit())
	{
		std::cout << "Could not initialize glfw\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create the window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learning Opengl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD \n";
		return -1;
	}

	//set initial the window dimensions
	glViewport(0, 0, 800, 600);

	//in case of resizing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//vertecies
	float vertecies[] = {
		 0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      1.0f, 1.0f,// top right
		 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f,// bottom right
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f,// bottom left
		-0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,      0.0f, 1.0f,// top left 
	};

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	VertexBuffer VBO{sizeof(vertecies), vertecies};

	IndexBuffer EBO{ sizeof(indices), indices };

	//vao is useful because all of the buffers get bound to it so when it comes
	//to drawing you only need to bind the vao instead of all the buffers individually
	VertexArray VAO{ GL_FLOAT };
	VAO.add_layout_element({ 3, GL_FALSE });
	VAO.add_layout_element({ 3, GL_FALSE });
	VAO.add_layout_element({ 2, GL_FALSE });
	VAO.compile_layout();


	//load all of the necessary shaders
	Shader shader{ "../../GLEngine/GLEngine/shaders/vertex.vert", "../../GLEngine/GLEngine/shaders/fragment.frag" };
	shader.bind();

	//add all the textures
	Texture2D texture{&shader};
	float border[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	texture.add_texture("../../GLEngine/GLEngine/res/brick.jpg", "ourTexture");
	texture.add_texture("../../GLEngine/GLEngine/res/wood.jpg", "ourTexture2");

	texture.bind_all();

	Renderer renderer;

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		process_input(window);

		//render
		renderer.draw(VBO, VAO, EBO, shader);

		//moves the back buffer to the front (Double buffering)
		glfwSwapBuffers(window);

		//poll for any events
		glfwPollEvents();
	}

	//cleanup
	glfwTerminate();

	return 0;
}