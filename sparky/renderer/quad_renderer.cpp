#include "quad_renderer.h"

QuadRenderer::QuadRenderer(int max_quad_cnt)
	:max_quad_cnt(max_quad_cnt), max_idx_cnt(max_quad_cnt * 6), max_buff_size(max_quad_cnt * sizeof(Vertex) * 4)
{
	// Resizing the buffer to its max capacity
	this->buffer.resize(this->max_buff_size);

	// Constructing the buffers
	this->vert_array = std::make_shared<VertexArray>();
	this->vert_buff = std::make_shared<VertexBuffer>(this->max_buff_size, nullptr, GL_DYNAMIC_DRAW);
	this->idx_buff = std::make_shared<IndexBuffer>(this->max_idx_cnt);

	// Vertex layouts
	this->vert_array->push_layout<float>(3, sizeof(Vertex));

	// Generating index buffer
	this->idx_buff->generate_quad_indices();
}

QuadRenderer::~QuadRenderer()
{
	this->buffer.clear();
}

void QuadRenderer::render_begin()
{
	this->buff_idx = 0;
	this->buffer.clear();
}

void QuadRenderer::render_end()
{
	// Pushing the vertex data into the vertex buffer
	this->vert_buff->bind();
	this->vert_buff->push_data(0, this->max_buff_size, this->buffer.data());

	// Drawcall
	this->vert_array->bind();
	GLCall(glDrawElements(GL_TRIANGLES, this->buff_idx, GL_UNSIGNED_INT, NULL));
}

Quad QuadRenderer::create_quad(glm::vec3 pos, glm::vec2 size)
{
	Quad quad;
	quad.vertex[0].pos = pos;
	quad.vertex[1].pos = glm::vec3(pos.x + size.x, pos.y, pos.z);
	quad.vertex[2].pos = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
	quad.vertex[3].pos = glm::vec3(pos.x, pos.y + size.y, pos.z);
	return quad;
}

void QuadRenderer::push_quad(const Quad& quad)
{
	for (int i = 0; i < 4; i++)
		this->buffer.push_back(quad.vertex[i]);
	this->buff_idx += 4 * VERTEX_CNT;
}
