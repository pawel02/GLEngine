#include "window/Window.h"

#include <iostream>

#include "./Renderer/Renderer.h"
#include "./Shapes/Cube.h"
#include "./textures/Texture2D.h"

#include "Player/Player.h"


int main()
{
	Window window{ std::move(Vector2<unsigned int>{800, 600}), "GLEngine", false };

	Cube<125>* cubes = new Cube<125>();

	for (float x = 0; x < 5; x++)
	{
		for (float z = 0; z < 5; z++)
		{
			cubes->AddCube(x, 0, z, 1, 0);
		}
	}


	//load all of the necessary shaders
	Shader shader{ "../../GLEngine/GLEngine/shaders/vertex.vert", "../../GLEngine/GLEngine/shaders/fragment.frag" };
	shader.bind();

	//add all the textures
	Texture2D texture{ &shader };
	float border[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	texture.add_texture("../../GLEngine/GLEngine/res/brick.jpg", "ourTexture2");
	texture.add_texture("../../GLEngine/GLEngine/res/wood.jpg", "ourTexture");

	texture.bind_all();

	Renderer renderer;

	//create the player
	Player player{ &window, shader };

	glm::mat4 model{ 1.0f };
	shader.set_uniform_mat4("model", model);

	//main loop
	while (!window.is_open())
	{

		renderer.clear();

		window.update();

		player.update(window.get_delta_time());

		renderer.draw(cubes->get_buffers().VBO, cubes->get_buffers().VAO, shader);

		window.after_update();
	}

	//cleanup
	glfwTerminate();
	delete cubes;

	return 0;
}
