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


	cubes->AddCube(0, 0, 0, 1, 0);


	Cube<1> light;
	light.AddCube(0, 0, 0, 1, 0);


	//load all of the necessary shaders
	Shader shader{ "../../GLEngine/GLEngine/shaders/vertex.vert", "../../GLEngine/GLEngine/shaders/fragment.frag" };
	Shader shaderLight{ "../../GLEngine/GLEngine/shaders/vertex.vert", "../../GLEngine/GLEngine/shaders/light.frag" };


	glm::vec3 LightPos(1.0f, 0.5f, 0.31f);
	shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
	
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
	player.add_shader(shaderLight);

	
	glm::mat4 model{ 1.0f };
	shader.bind();
	shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
	shader.set_uniform_mat4("model", model);
	

	glm::vec3 lightPos{ 1.2f, 1.0f, 2.0f };
	shader.set_vec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);

	glm::mat4 model2{ 1.0f };

	shaderLight.bind();
	model2 = glm::translate(model2, lightPos);
	model2 = glm::scale(model2, glm::vec3(0.2f));
	shaderLight.set_uniform_mat4("model", model2);

	//main loop
	while (!window.is_open())
	{

		renderer.clear();

		window.update();

		//make the light rotate
		lightPos[0] = (window.get_delta_time()) + lightPos[0];

		shader.bind();
		shader.set_vec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);

		player.update(window.get_delta_time());
		
		renderer.draw(cubes->get_buffers().VBO, cubes->get_buffers().VAO, shader);
		
		model2 = glm::mat4{ 1.0f };
		shaderLight.bind();
		model2 = glm::translate(model2, lightPos);
		model2 = glm::scale(model2, glm::vec3(0.2f));
		shaderLight.set_uniform_mat4("model", model2);
		renderer.draw(cubes->get_buffers().VBO, cubes->get_buffers().VAO, shaderLight);

		window.after_update();
	}

	//cleanup
	glfwTerminate();
	delete cubes;

	return 0;
}
