#pragma once
#include "dependency.h"
#include "../core/core.h"

class VertexBuffer
{
public:
	VertexBuffer(int size, void* data, int flag);
	~VertexBuffer();

	void push_data(int start_sz, int end_sz, void* data);

public:
	void bind();
	void unbind();

public:
	inline int get_size()    const { return size; }
	inline int get_buff_id() const { return buff_id; }

private:
	unsigned int buff_id;
	int size;
};
