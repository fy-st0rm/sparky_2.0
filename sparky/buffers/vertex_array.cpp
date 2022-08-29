#include "vertex_array.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &this->buff_id));
	GLCall(glBindVertexArray(this->buff_id));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &this->buff_id));
}

void VertexArray::bind()
{
	GLCall(glBindVertexArray(this->buff_id));
}

void VertexArray::unbind()
{
	GLCall(glBindVertexArray(0));
}


