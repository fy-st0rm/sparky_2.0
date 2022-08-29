#pragma once
#include "../buffers/buffers.h"
#include "vertex.h"


class QuadRenderer
{
public:
	QuadRenderer(int max_quad_cnt);
	~QuadRenderer();

public:
	// Render functions
	void render_begin();
	void render_end();

	Quad create_quad(glm::vec3 pos, glm::vec2 size);
	void push_quad(const Quad& quad);

private:
	int max_quad_cnt;
	int max_idx_cnt;
	int max_buff_size;

	// Vertices buffer
	int buff_idx;
	std::vector<Vertex> buffer;

private:
	std::shared_ptr<VertexArray> vert_array;
	std::shared_ptr<VertexBuffer> vert_buff;
	std::shared_ptr<IndexBuffer> idx_buff;
};
