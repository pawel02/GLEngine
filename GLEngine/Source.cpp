#include "window/Window.h"

#include <iostream>

#include "./Renderer/Renderer.h"
#include "./Shapes/Quad.h"
#include "./textures/Texture2D.h"

#include "Player/Player.h"


int main()
{
	Window window{ std::move(Vector2<unsigned int>{800, 600}), "GLEngine", false };

	//create a simple grid
	Quad<1000> quads;
	float TexID = 1.0f;
	for (float x = 0; x < 5; x++)
	{
		for (float y = 0; y < 5; y++)
		{
			TexID = TexID == 1.0f ? 0.0f : 1.0f;
			quads.AddQuad(x, y, 1, TexID);
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
		Player::get_camera().update();

		renderer.draw(quads.get_buffers(), shader);

		window.after_update();
	}

	//cleanup
	glfwTerminate();

	return 0;
}
