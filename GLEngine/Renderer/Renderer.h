#pragma once
#include "../shaders/Shader.h"
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
	void draw(VertexBuffer& VBO, VertexArray& VAO, Shader& shader);

	void clear();
};