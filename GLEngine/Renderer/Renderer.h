#pragma once
#include "../Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct Buffers
{
	VertexArray& VAO;
	IndexBuffer& EBO;
	VertexBuffer& VBO;
};

class Renderer
{
public:
	Renderer() noexcept { init(); };
	Renderer(bool isWireframe) noexcept;
	~Renderer() = default;
	
	void init() const;

	void draw(VertexBuffer& VBO, VertexArray& VAO, IndexBuffer& EBO, Shader& shader);
	void draw(Buffers& buffers, Shader& shader);

	void clear();
};