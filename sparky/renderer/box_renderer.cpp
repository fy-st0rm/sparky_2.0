#include "box_renderer.h"

BoxRenderer::BoxRenderer(int max_quad_cnt)
	:max_quad_cnt(max_quad_cnt), max_idx_cnt(max_quad_cnt * 6), max_buff_size(max_quad_cnt * sizeof(Vertex) * 4)
{
	std::vector<Vertex> buffer;
	Vertex a = {glm::vec3(-0.5, -0.5, 0.0f)};
	Vertex b = {glm::vec3(-0.5,  0.5, 0.0f)};
	Vertex c = {glm::vec3( 0.5,  0.5, 0.0f)};
	Vertex d = {glm::vec3( 0.5, -0.5, 0.0f)};
	buffer.push_back(a);
	buffer.push_back(b);
	buffer.push_back(c);
	buffer.push_back(d);

	this->vert_array = std::make_shared<VertexArray>();
	this->vert_buff = std::make_shared<VertexBuffer>(this->max_buff_size, buffer.data(), GL_STATIC_DRAW);
	this->idx_buff = std::make_shared<IndexBuffer>(this->max_idx_cnt);

	this->vert_array->push_layout<float>(3, sizeof(Vertex));
	this->idx_buff->generate_quad_indices();
}

BoxRenderer::~BoxRenderer()
{
}

void BoxRenderer::render()
{
	this->vert_array->bind();
	GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL));
}

