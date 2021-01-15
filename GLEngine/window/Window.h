#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include "../util/Primitives.h"

class Window
{
	const Vector2<unsigned int> size;

	GLFWwindow* window;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

public:
	explicit Window(Vector2<unsigned int>&& size, const char* name, bool show_mouse) noexcept;
	~Window() noexcept;

	GLFWwindow* get_window() const { return window; }
	const Vector2<unsigned int>& get_size() const { return size; }
	float get_delta_time() const { return deltaTime; }

	void make_current();
	bool is_open();

	void update();
	void after_update();
};