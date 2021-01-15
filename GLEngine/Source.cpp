#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "./Renderer/Renderer.h"
#include "./textures/Texture2D.h"

#include "Camera/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float fov = 45.0f;

Camera camera{nullptr, 2.5f};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


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
	GLFWwindow* window = glfwCreateWindow(800, 600, "GLEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	//mouse input
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


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


	VertexBuffer VBO{sizeof(vertices), vertices };

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
	Texture2D texture{&shader};
	float border[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	texture.add_texture("../../GLEngine/GLEngine/res/brick.jpg", "ourTexture");
	texture.add_texture("../../GLEngine/GLEngine/res/wood.jpg", "ourTexture2");

	texture.bind_all();

	Renderer renderer;

	//matrix maths
	//movement of the object
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//camera
	camera = Camera{ &shader, 2.5f };

	//how you want the camera to see
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


	//model is set in the main loop
	//view is set by the camera
	shader.set_uniform_mat4("projection", projection);

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

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		process_input(window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//move the camera around
		camera.update();

		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePos[i]);

			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
				glm::vec3(0.5f, 1.0f, 0.0f));
			shader.set_uniform_mat4("model", model);

			renderer.draw(VBO, VAO, shader);
		}

		//moves the back buffer to the front (Double buffering)
		glfwSwapBuffers(window);

		//poll for any events
		glfwPollEvents();
	}

	//cleanup
	glfwTerminate();

	return 0;
}


void process_input(GLFWwindow* window)
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