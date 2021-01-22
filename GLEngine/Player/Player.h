#pragma once
#include "../window/Window.h"
#include "../Camera/Camera.h"

class Player 
{
	Window* window;

	GLFWwindow* g_window;

	bool isWireframe = false;
	bool isKeyDown = false;
	
	Camera camera;
public:
	//this is temporary later on this will not be static once an event system is built

	explicit Player(Window* window, Shader& shader) noexcept;
	~Player() noexcept;

	void update(float deltaTime);

	inline Camera& get_camera() { return camera; }
};