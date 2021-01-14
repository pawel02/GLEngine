#include "Renderer.h"

Renderer::Renderer(bool isWireframe) noexcept
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::draw(VertexBuffer& VBO, VertexArray& VAO, IndexBuffer& EBO, Shader& shader)
{
	VBO.bind();
	VAO.bind();
	EBO.bind();
	shader.bind();

	glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::draw(Buffers& buffers, Shader& shader)
{
	buffers.VBO.bind();
	buffers.VAO.bind();
	buffers.EBO.bind();
	shader.bind();

	glDrawElements(GL_TRIANGLES, buffers.EBO.getCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::clear()
{
	glClearColor(0.2, 0.5, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}
