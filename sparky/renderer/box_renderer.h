#pragma once
#include "../buffers/buffers.h"
#include "vertex.h"


class BoxRenderer
{
public:
	BoxRenderer(int max_quad_cnt);
	~BoxRenderer();

	void render();

private:
	int max_quad_cnt;
	int max_idx_cnt;
	int max_buff_size;

private:
	std::shared_ptr<VertexArray> vert_array;
	std::shared_ptr<VertexBuffer> vert_buff;
	std::shared_ptr<IndexBuffer> idx_buff;
};
