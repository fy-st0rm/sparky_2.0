#include "text_renderer.h"

namespace Sparky {
	TextRenderer::TextRenderer(const std::string& font_path, int font_size, int max_quad_cnt, std::shared_ptr<OrthoCamera> camera)
		:font_path(font_path), font_size(font_size), max_quad_cnt(max_quad_cnt), max_idx_cnt(max_quad_cnt * 6), max_buff_size(max_quad_cnt * sizeof(Vertex) * 4), camera(camera), white_texture(0)
	{
		// Resizing the buffer to its max capacity
		this->buffer = (float*) malloc(this->max_buff_size);
	
		// Constructing the buffers
		this->vert_array = std::make_shared<VertexArray>();
		this->vert_buff  = std::make_shared<VertexBuffer>(this->max_buff_size, nullptr, GL_DYNAMIC_DRAW);
		this->idx_buff   = std::make_shared<IndexBuffer>(this->max_idx_cnt);
	
		// Vertex layouts
		this->vert_array->push_layout<float>(3, sizeof(Vertex));
		this->vert_array->push_layout<float>(4, sizeof(Vertex));
		this->vert_array->push_layout<float>(2, sizeof(Vertex));
		this->vert_array->push_layout<float>(1, sizeof(Vertex));
	
		// Generating index buffer
		this->idx_buff->generate_quad_indices();

		// Generating default shader
		this->shader = std::make_shared<Shader>();
		this->generate_default_texture();
		this->provide_texture_samplers();

		// Loading the font
		this->font = (TTF_Font*) SPGuard::sdl_check_ptr(TTF_OpenFont(this->font_path.c_str(), this->font_size));
	}
	
	TextRenderer::~TextRenderer()
	{
		TTF_CloseFont(this->font);
		delete this->buffer;
		GLCall(glDeleteTextures(1, &this->white_texture));
	}
	
	void TextRenderer::generate_default_texture()
	{
		// Generating a white texture
		GLCall(glGenTextures(1, &this->white_texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, this->white_texture));

		unsigned int white = 0xffffffff;
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &white));

		this->texture_slots.push_back(this->white_texture);
	}
	
	void TextRenderer::bind_all_textures()
	{
		// Binding the texture units according to their texture id
		// slot = [0, , 2, 3, , 4] => Binds according to their id rather then linearly to prevent missmatch of the index in shader
		for (int i = 0; i < this->texture_slots.size(); i++)
		{
			unsigned int id = this->texture_slots[i];
			GLCall(glBindTextureUnit(id, id));
		}
	}
	
	void TextRenderer::provide_texture_samplers()
	{
		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
	
		// Providing samplers to the shader
		int loc = this->shader->get_uniform_location("textures");
		GLCall(glUniform1iv(loc, 32, samplers));
	}

	void TextRenderer::switch_shader_from_string(const std::string& vert_shader, const std::string& frag_shader)
	{
		this->shader->load_shader_from_string(vert_shader, frag_shader);
		this->shader->bind();
		this->provide_texture_samplers();
	}

	void TextRenderer::switch_shader_from_file(const std::string& vert_shader_file, const std::string& frag_shader_file)
	{
		this->shader->load_shader_from_file(vert_shader_file, frag_shader_file);
		this->shader->bind();
		this->provide_texture_samplers();
	}
	
	void TextRenderer::render_begin()
	{
		// Clearning the buffer
		this->buff_idx = 0;
		memset(this->buffer, 0, this->max_buff_size);
	}
	
	void TextRenderer::render_end()
	{
		// Binding shader and texture
		this->shader->bind();
		this->bind_all_textures();

		// Updating the camera
		this->camera->update(this->shader.get());
	
		// Pushing the vertex data into the vertex buffer
		this->vert_buff->bind();
		this->vert_buff->push_data(0, this->max_buff_size, this->buffer);
	
		// Drawcall
		this->vert_array->bind();
		GLCall(glDrawElements(GL_TRIANGLES, this->buff_idx, GL_UNSIGNED_INT, NULL));
	}

	Quad TextRenderer::create_quad(glm::vec3 pos, glm::vec2 size, glm::vec4 color, glm::vec4 tex_cord, Texture* texture)
	{
		// Adding texture to the slots if it is new
		int id = -1;
		for (auto& i : this->texture_slots)
		{
			if (i == texture->get_texture_id())
				id = i;
		}
		if (texture->get_texture_id() == SparkyWhiteTextureID)
		{
			id = this->white_texture;
		}
		else if (id == -1)
		{
			this->texture_slots.push_back(texture->get_texture_id());
			id = texture->get_texture_id();
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
	
	void TextRenderer::push_quad(const Quad& quad)
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

	void TextRenderer::push_text(const std::string& text, glm::vec3 pos, glm::vec4 color)
	{
		std::shared_ptr<Texture> texture;

		// If texture doesnt exists in cache buffer
		if (this->texture_cache.find(text) == this->texture_cache.end())
		{
			this->handle_cache_overflow();

			// Creating SDL Surface
			SDL_Color sdl_color = { 255, 255, 255, 255 };
			SDL_Surface* surface = (SDL_Surface*) SPGuard::sdl_check_ptr(TTF_RenderText_Blended(this->font, text.c_str(), sdl_color));

			// Creating texture from surface and deleting surface by (load_from_sdl_surface)
			texture = std::make_shared<Texture>();
			texture->load_from_sdl_surface(surface);

			// Adding the texture to the cache for future use
			this->texture_cache[text] = texture;
		}
		else
		{
			texture = this->texture_cache[text];
		}
		
		// Creating a quad from the texture and rendering it
		glm::vec2 size = { texture->get_width(), texture->get_height() };
		Quad quad = this->create_quad(pos, size, color, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.get());
		this->push_quad(quad);
	}

	void TextRenderer::handle_cache_overflow()
	{
		if (this->texture_cache.size() >= this->max_texture_cache)
			this->texture_cache.erase(this->texture_cache.begin());
	}
	
	void TextRenderer::print_buffer()
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
