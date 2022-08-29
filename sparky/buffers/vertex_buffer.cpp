#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(int size, void* data, int flag)
	:size(size)
{
	GLCall(glGenBuffers(1, &this->buff_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->buff_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, flag));
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->buff_id);
}

void VertexBuffer::push_data(int start_sz, int end_sz, void* data)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->buff_id));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, start_sz, end_sz, data));
}

void VertexBuffer::bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->buff_id));
}

void VertexBuffer::unbind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
