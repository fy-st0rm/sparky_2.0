#pragma once
#include "dependency.h"
#include "../core/core.h"

class IndexBuffer
{
public:
	IndexBuffer(int idx_cnt);
	~IndexBuffer();

public:
	void bind();
	void unbind();
	void generate_quad_indices();

public:
	unsigned int get_buff_id() const { return this->buff_id; }
	std::vector<unsigned int> get_indices() const { return this->indices; }

private:
	unsigned int buff_id;
	int idx_cnt, size;
	std::vector<unsigned int> indices;
};
