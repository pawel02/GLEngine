#pragma once
#include "ITexture.h"

class Texture2D : public virtual ITexture
{
public:
	explicit Texture2D(Shader* shader) noexcept;
	explicit Texture2D() noexcept;

	~Texture2D() noexcept;

	// Inherited via ITexture
	virtual void settings(float border[4], unsigned int mode = GL_REPEAT, unsigned int min_filter = GL_NEAREST, unsigned int max_filter = GL_LINEAR, unsigned int mipmap = GL_LINEAR_MIPMAP_LINEAR) override;

	virtual bool add_texture(const char* filename, const std::string& texture_name) override;

	virtual void bind(const std::string& texture_name) override;

	virtual void delete_texture(const std::string& texture_name) override;

	virtual void bind_all() override;

	virtual void delete_all() override;

private:
	void is_shader_bound();
};