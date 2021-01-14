#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <string>
#include "Shader.h"

struct TextureID
{
	unsigned int set_id;
	unsigned int gen_id;
};

/*
Base class for the textures

After binding the texture you may need to also 
set the sample uniform shader variable to the texture position if you have
not given the texture a shader to work with
*/
class ITexture
{
public:
	ITexture(Shader* s)
		:shader{s}
	{}

	ITexture()
		:shader{nullptr}
	{}

	/*
	set as many or as little custom settings as you would like
	
	@params
	mode   - is the TEXTURE_WRAP mode for all axis
	border - is the border color (only need to be set when mode is GL_CLAMP_TO_BORDER)
	min_filter - when downscaling what mode should be used
	max_filter - when upscaling the texture what mode should be used
	mipmap - what mipmap mode you want to use
	*/
	virtual void settings(
		float border[4], 
		unsigned int mode = GL_REPEAT,
		unsigned int min_filter = GL_NEAREST,
		unsigned int max_filter = GL_LINEAR,
	    unsigned int mipmap = GL_LINEAR_MIPMAP_LINEAR) = 0;

	//returns true if the texture was loaded successfully
	virtual bool add_texture(const char* filename, const std::string& texture_name) = 0;

	//Bind the specified texture
	virtual void bind(const std::string& texture_name)   = 0;
	
	//Unbind the specified texture
	virtual void delete_texture(const std::string& texture_name) = 0;

	//returns all of the texture ids
	virtual const std::unordered_map<std::string, TextureID> getIds() const
	{
		return texIds;
	};

	//bind all of the textures
	virtual void bind_all()   = 0;

	//unbind all of the textures
	virtual void delete_all() = 0;

	virtual void bind_shader(Shader* shader)
	{
		this->shader = shader;
	}

protected:
	/*
	the string should be set to the variable name used in the fragment shader
	*/
	std::unordered_map<std::string, TextureID> texIds;

	Shader* shader = nullptr;
};

