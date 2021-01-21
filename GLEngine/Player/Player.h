#pragma once
#include "../window/Window.h"
#include "../Camera/Camera.h"

class Player 
{
	Window* window;

	GLFWwindow* g_window;
public:
	//this is temporary later on this will not be static once an event system is built
	static Camera camera;

	explicit Player(Window* window, Shader& shader) noexcept;
	~Player() noexcept;

	void update(float deltaTime);

	//currently there should only be 1 camera
	static Camera& get_camera() { return camera; }
};