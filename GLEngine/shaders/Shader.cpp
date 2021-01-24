#include "Shader.h"
#include <glad/glad.h>

#include <fstream>
#include <iostream>

Shader::Shader()
{
	shader = glCreateProgram();
}

Shader::Shader(const char* vertex, const char* fragment)
{
	shader = glCreateProgram();

	load_shader(vertex, GL_VERTEX_SHADER);
	load_shader(fragment, GL_FRAGMENT_SHADER);

}

Shader::~Shader()
{
	glDeleteProgram(shader);
}

void Shader::bind()
{
	glUseProgram(shader);
}

void Shader::un_bind()
{
	glUseProgram(0);
}

bool Shader::compile_shader(unsigned int& m_shader)
{
	glCompileShader(m_shader);

	int success;
	char infoLog[512];
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		//gather some info about the compile error
		glGetShaderInfoLog(m_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER could not compile shader\n" << infoLog << "\n";
		return false;
	}
	glAttachShader(shader, m_shader);

	return true;
}

bool Shader::link_shader()
{
	glLinkProgram(shader);

	return false;
}

int Shader::get_uniform_location(const std::string& name)
{
	if (uniform_location_cache.find(name) == uniform_location_cache.end())
	{
		//find the item and add to cache
		uniform_location_cache[name] = glGetUniformLocation(shader, name.c_str());
	}

	return uniform_location_cache[name];
}

bool Shader::load_shader(const char* filename, unsigned int shader_type)
{
	std::ifstream file(filename);
	std::string shader_source = "";
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			shader_source += line + "\n";
		}

		//create the shader
		unsigned int m_shader = glCreateShader(shader_type);

		//this is unfortunately necessary since glShaderSource takes a const char** so this has to
		//be a local variable
		const char* shader_source_use = shader_source.c_str();
		
		glShaderSource(m_shader, 1, &shader_source_use, NULL);

		if (!compile_shader(m_shader))
		{
			glDeleteShader(m_shader);
			goto cleanup;
		}

		bool link = link_shader();
		
		//shader no longer needed its stored in the program
		glDeleteShader(m_shader);

		if (!link)
		{
			goto cleanup;
		}
	}
	else
	{
		std::cout << "could not open the file specified\n";
		goto cleanup;
	}	

	file.close();
	return true;

cleanup:
	file.close();
	return false;
}

void Shader::set_uniform_4f(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(get_uniform_location(name), x, y, z, w);
}

void Shader::set_vec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(get_uniform_location(name), x, y, z);
}

void Shader::set_uniform_mat4(const std::string& name, glm::mat4 mat)
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_uniform_1i(const std::string& name, int x)
{
	glUniform1i(get_uniform_location(name), x);

}

void Shader::set_Float(const std::string& name, float x)
{
	glUniform1f(get_uniform_location(name), x);
}

void Shader::set_uniform_1iv(const std::string& name, int size, int* arr)
{
	glUniform1iv(get_uniform_location(name), size, arr);
}
