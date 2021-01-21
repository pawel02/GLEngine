#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"

#include <iostream>
#include <algorithm>
#include <vector>

Texture2D::Texture2D(Shader* shader) noexcept
	: ITexture{shader}
{
	stbi_set_flip_vertically_on_load(true);
}

Texture2D::Texture2D() noexcept
	: ITexture{}
{
	stbi_set_flip_vertically_on_load(true);
}

Texture2D::~Texture2D() noexcept
{
	delete_all();
}

void Texture2D::settings(
    float border[4], 
    unsigned int mode, 
    unsigned int min_filter, 
    unsigned int max_filter,
    unsigned int mipmap)
{

	//configuring textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);

	//set the border color for the texture
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);


	//these are texture sampling methods
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter); //sharper more blocky good for textures scaled down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max_filter);  //less sharp more smudgy good for texture scaled up

	//mipmaps for saving memory when dealing with small objects
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmap);

}

bool Texture2D::add_texture(const char* filename, const std::string& texture_name)
{
	// atm we are limited to only 16 textures which is the max for opengl
	if (texIds.size() != 16)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

		if (!data)
		{
			std::cout << "Could not load the image " << filename << "\n";
			stbi_image_free(data);
			return false;
		}

		//make sure that if the name already exists then you delete the texture under that
		if (texIds.find(texture_name) != texIds.end())
		{
			glDeleteTextures(1, &texIds[texture_name].gen_id);
		}

		//find the first id which is not being used
		unsigned int id = GL_TEXTURE0;
		for (auto&& x : texIds)
		{
			auto it = std::find_if(texIds.begin(), texIds.end(),
				[&id](std::pair<std::string, TextureID> item) -> bool {
					if (item.second.set_id == id)
					{
						return true;
					}
					return false;
				});

			if (it == texIds.end())
			{
				break;
			}
			id++;
		}
		texIds[texture_name].set_id = id;
		glActiveTexture(id);
		glGenTextures(1, &texIds[texture_name].gen_id);
		
		glBindTexture(GL_TEXTURE_2D, texIds[texture_name].gen_id);

		//copy the image data to the buffer for the moment only RGB images are supported
		//in the future look at image type to determine color scheme
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);


		stbi_image_free(data);
		return true;
	}

	std::cout << "maximum amount of textures assigned\n";
	return false;
}

void Texture2D::bind(const std::string& texture_name)
{
	is_shader_bound();

	glBindTexture(GL_TEXTURE_2D, texIds[texture_name].gen_id);
	shader->set_uniform_1i(texture_name, texIds[texture_name].set_id - GL_TEXTURE0);
}

void Texture2D::delete_texture(const std::string& texture_name)
{
	is_shader_bound();

	glDeleteTextures(1, &texIds[texture_name].gen_id);

	texIds.erase(texture_name);
}

void Texture2D::bind_all() 
{
	is_shader_bound();
	uint16_t i = 0;
	std::vector<int> samplers{};
	for (auto&& id : texIds)
	{
		glBindTexture(GL_TEXTURE_2D, id.second.gen_id);

		samplers.push_back(i);
		i++;
	}

	shader->set_uniform_1iv("u_Textures", samplers.size(), samplers.data());
}

void Texture2D::delete_all() 
{
	is_shader_bound();
	for (auto&& id : texIds)
	{
		is_shader_bound();

		glDeleteTextures(1, &id.second.gen_id);
	}

	texIds.clear();
}

void Texture2D::is_shader_bound()
{
	if (!shader)
		std::cout << "make sure that you bind the shader\n";
}
