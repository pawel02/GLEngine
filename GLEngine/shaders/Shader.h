#pragma once
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
/*
Two use cases normal is supplying the files for the vertex and fragment shader to the constructor

More verbose would be to construct the shader
Load all the necessary shaders individually

The more verbose method should be used if you want to load more shaders into the program
*/
class Shader
{
private:
	unsigned int shader = 0;

	std::unordered_map<std::string, int> uniform_location_cache;
public:
	Shader();

	//convinience constructor
	Shader(const char* vertex, const char* fragment);
	~Shader();

	void bind();
	void un_bind();

	inline unsigned int get_program() const
	{
		return shader;
	}

	bool load_shader(const char* filename, unsigned int shader_type);

	//setting uniforms
	void set_uniform_4f(const std::string& name, float x, float y, float z, float w);
	void set_vec3(const std::string& name, float x, float y, float z);

	void set_uniform_mat4(const std::string& name, glm::mat4 mat);
	void set_uniform_1i(const std::string& name, int x);
	void set_Float(const std::string& name, float x);

	void set_uniform_1iv(const std::string& name, int size, int* arr);

private:

	//these will be called by the load_shader so the client does not need access to these
	bool compile_shader(unsigned int& m_shader);
	bool link_shader();

	//retrieves the location of a given uniform
	int get_uniform_location(const std::string& name);
};

