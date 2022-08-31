#include "index_buffer.h"

namespace Sparky {
	IndexBuffer::IndexBuffer(int idx_cnt)
		:idx_cnt(idx_cnt), size(idx_cnt * sizeof(int))
	{
		GLCall(glGenBuffers(1, &this->buff_id));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buff_id));
	}
	
	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &this->buff_id));
	}
	
	void IndexBuffer::bind()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buff_id));
	}
	
	void IndexBuffer::unbind()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
	
	void IndexBuffer::generate_quad_indices()
	{
		this->indices.resize(this->idx_cnt);
		for (int offset = 0, i = 0; i < this->idx_cnt; i += 6) 
		{
			this->indices[0 + i] = 0 + offset;
			this->indices[1 + i] = 1 + offset;
			this->indices[2 + i] = 2 + offset;
	
			this->indices[3 + i] = 2 + offset;
			this->indices[4 + i] = 3 + offset;
			this->indices[5 + i] = 0 + offset;
			offset += 4;
		}
		this->bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices.data(), GL_STATIC_DRAW));
	}
}
