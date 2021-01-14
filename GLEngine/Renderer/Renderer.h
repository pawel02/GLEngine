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
	Renderer() = default;
	Renderer(bool isWireframe) noexcept;
	~Renderer() = default;
	
	void draw(VertexBuffer& VBO, VertexArray& VAO, IndexBuffer& EBO, Shader& shader);
	void draw(Buffers& buffers, Shader& shader);

	void clear();
};