#include "quad_renderer.h"

namespace Sparky {
	QuadRenderer::QuadRenderer(int max_quad_cnt)
		:max_quad_cnt(max_quad_cnt), max_idx_cnt(max_quad_cnt * 6), max_buff_size(max_quad_cnt * sizeof(Vertex) * 4)
	{
		// Resizing the buffer to its max capacity
		this->buffer = (float*) malloc(this->max_buff_size);
	
		// Constructing the buffers
		this->vert_array = std::make_shared<VertexArray>();
		this->vert_buff  = std::make_shared<VertexBuffer>(this->max_buff_size, nullptr, GL_DYNAMIC_DRAW);
		this->idx_buff   = std::make_shared<IndexBuffer>(this->max_idx_cnt);
	
		// Constructing shader
		this->shader = std::make_shared<Shader>();
		this->shader->load_shader_from_string(SPARKY_DEFAULT_VERT_SHADER, SPARKY_DEFAULT_FRAG_SHADER);
		this->shader->bind();
	
		// Vertex layouts
		this->vert_array->push_layout<float>(3, sizeof(Vertex));
		this->vert_array->push_layout<float>(4, sizeof(Vertex));
		this->vert_array->push_layout<float>(2, sizeof(Vertex));
		this->vert_array->push_layout<float>(1, sizeof(Vertex));
	
		// Generating index buffer
		this->idx_buff->generate_quad_indices();
	
		// Generating default texture
		this->generate_default_texture();
		this->provide_texture_samplers();
	
	}
	
	QuadRenderer::~QuadRenderer()
	{
		delete this->buffer;
	}
	
	void QuadRenderer::generate_default_texture()
	{
		unsigned int white = 0xffffffff;
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &white));
		this->texture_slots.push_back(0); // 0 = white texture slot
	}
	
	void QuadRenderer::bind_all_textures()
	{
		for (int i = 0; i < this->texture_slots.size(); i++)
		{
			GLCall(glBindTextureUnit(i, this->texture_slots[i]));
		}
	}
	
	void QuadRenderer::provide_texture_samplers()
	{
		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
	
		// Providing samplers to the shader
		int loc = this->shader->get_uniform_location("textures");
		GLCall(glUniform1iv(loc, 32, samplers));
	}
	
	void QuadRenderer::render_begin()
	{
		this->buff_idx = 0;
		memset(this->buffer, 0, this->max_buff_size);
	}
	
	void QuadRenderer::render_end()
	{
		// Binding all the textures
		this->bind_all_textures();
	
		// Pushing the vertex data into the vertex buffer
		this->vert_buff->bind();
		this->vert_buff->push_data(0, this->max_buff_size, this->buffer);
	
		// Drawcall
		this->shader->bind();
		this->vert_array->bind();
		GLCall(glDrawElements(GL_TRIANGLES, this->buff_idx, GL_UNSIGNED_INT, NULL));
	}
	
	Quad QuadRenderer::create_quad(glm::vec3 pos, glm::vec2 size, glm::vec4 color,glm::vec4 tex_cord, const Texture& texture)
	{
		// Adding texture to the slots if it is new
		int id = -1;
		for (auto& i : this->texture_slots)
		{
			if (i == texture.get_texture_id())
				id = i;
		}
		if (id == -1)
		{
			this->texture_slots.push_back(texture.get_texture_id());
			id = texture.get_texture_id();
		}
	
		Quad quad;
	
		// Quad position
		quad.vertex[0].pos = pos;
		quad.vertex[1].pos = glm::vec3(pos.x + size.x, pos.y, pos.z);
		quad.vertex[2].pos = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
		quad.vertex[3].pos = glm::vec3(pos.x, pos.y + size.y, pos.z);
	
		// Quad color
		quad.vertex[0].color = color;
		quad.vertex[1].color = color;
		quad.vertex[2].color = color;
		quad.vertex[3].color = color;
	
		// Quad texture coordinate
		quad.vertex[0].tex_cord = tex_cord;
		quad.vertex[1].tex_cord = glm::vec2(tex_cord.x + tex_cord.z, tex_cord.y);
		quad.vertex[2].tex_cord = glm::vec2(tex_cord.x + tex_cord.z, tex_cord.y + tex_cord.w);
		quad.vertex[3].tex_cord = glm::vec2(tex_cord.x, tex_cord.y + tex_cord.w);
	
		// Quad Texture id
		for (int i = 0; i < 4; i++)
			quad.vertex[i].tex_id = id;
	
		return quad;
	}
	
	void QuadRenderer::push_quad(const Quad& quad)
	{
		if (this->buff_idx >= this->max_quad_cnt * 4 * VERTEX_SIZE)
		{
			this->render_end();
			this->render_begin();
		}
	
		for (int i = 0; i < 4; i++)
		{
			this->buffer[this->buff_idx++] = quad.vertex[i].pos.x;
			this->buffer[this->buff_idx++] = quad.vertex[i].pos.y;
			this->buffer[this->buff_idx++] = quad.vertex[i].pos.z;
			this->buffer[this->buff_idx++] = quad.vertex[i].color.r;
			this->buffer[this->buff_idx++] = quad.vertex[i].color.g;
			this->buffer[this->buff_idx++] = quad.vertex[i].color.b;
			this->buffer[this->buff_idx++] = quad.vertex[i].color.a;
			this->buffer[this->buff_idx++] = quad.vertex[i].tex_cord.x;
			this->buffer[this->buff_idx++] = quad.vertex[i].tex_cord.y;
			this->buffer[this->buff_idx++] = quad.vertex[i].tex_id;
		}
	}
	
	void QuadRenderer::print_buffer()
	{
		std::cout << "Printing buffer:\n";
		int j = 0, k = 0;
		for (int i = 0; i < this->buff_idx; i++)
		{
			j++;
			std::cout << this->buffer[i] << " ";
			if (j == VERTEX_SIZE)
			{
				std::cout << std::endl;
				j = 0;
				k++;
			}
			if (k == 4)
			{
				std::cout << std::endl;
				k = 0;
			}
		}
	}
}
