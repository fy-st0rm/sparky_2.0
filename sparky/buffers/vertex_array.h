#pragma once
#include "dependency.h"
#include "../core/core.h"


namespace Sparky {
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
	
		template<typename T>
		void push_layout(int count, int stride)
		{
			GLCall(glEnableVertexAttribArray(this->layout_idx));
			GLCall(glVertexAttribPointer(this->layout_idx, count, this->get_gl_type<T>(), GL_FALSE, stride, (const void*) this->layout_offset));
			this->layout_idx++;
			this->layout_offset += count * sizeof(T);
		}
	
	public:
		void bind();
		void unbind();
	
	public:
		inline int get_buff_id() const { return buff_id; }
	
	private:
		template <typename T>
		unsigned int get_gl_type()
		{
			if (typeid(T) == typeid(float))        return GL_FLOAT;
			if (typeid(T) == typeid(int))          return GL_INT;
			if (typeid(T) == typeid(unsigned int)) return GL_UNSIGNED_INT;
			SP_ASSERT(false);
		}
	
	private:
		unsigned int buff_id;
		unsigned int layout_idx = 0;
		size_t layout_offset = 0;
	};
}
