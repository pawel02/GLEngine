#include "window/Window.h"

#include <iostream>

#include "./Renderer/Renderer.h"
#include "./textures/Texture2D.h"

#include "Player/Player.h"


int main()
{
	//initialize glfw
	if (!glfwInit())
	{
		std::cout << "Could not initialize glfw\n";
		return -1;
	}

	Window window{ std::move(Vector2<unsigned int>{800, 600}), "GLEngine", false };


	//vertices
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

	//create the player
	Player player{ &window, shader };

	//main loop
	while (!window.is_open())
	{
		renderer.clear();

		window.update();

		player.update(window.get_delta_time());
		Player::get_camera().update();

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
