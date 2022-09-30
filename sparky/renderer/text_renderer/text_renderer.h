#pragma once
#include "../../buffers/buffers.h"
#include "../../shader/shader.h"
#include "../../texture/texture.h"
#include "../../camera/ortho_cam.h"
#include "../vertex.h"

namespace Sparky {
	class TextRenderer
	{
	public:
		TextRenderer(const std::string& font_path, int font_size, int max_quad_cnt, std::shared_ptr<OrthoCamera> camera);
		~TextRenderer();
	
	public:
		// Render functions
		void render_begin();
		void render_end();
	
		void push_text(const std::string& text, glm::vec3 pos, glm::vec4 color);
		void print_buffer();

	public:
		// Getters and setters
		std::shared_ptr<Shader> get_shader() const { return this->shader; }

		int  get_max_texture_cache() const  { return this->max_texture_cache; }
		void set_max_texture_cache(int amt) { this->max_texture_cache = amt; } 

		void switch_shader_from_string(const std::string& vert_shader, const std::string& frag_shader);
		void switch_shader_from_file  (const std::string& vert_shader_file, const std::string& frag_shader_file);
	
	public:
		void generate_default_texture();
		void bind_all_textures();
		void provide_texture_samplers();
	
	private:
		Quad create_quad(glm::vec3 pos, glm::vec2 size, glm::vec4 color, glm::vec4 tex_cord, Texture* texture);
		void push_quad(const Quad& quad);
		
		void handle_cache_overflow();

	private:
		int max_quad_cnt;
		int max_idx_cnt;
		int max_buff_size;
		int max_texture_cache = 100;

		// Fonts
		std::string font_path;
		int font_size;
		TTF_Font* font;
			
		// Text texture cache
		std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache;

		// Vertices buffer
		int buff_idx;
		float* buffer;
	
		// Texture buffer
		unsigned int white_texture;
		std::vector<float> texture_slots;
	
	private:
		std::shared_ptr<VertexArray> vert_array;
		std::shared_ptr<VertexBuffer> vert_buff;
		std::shared_ptr<IndexBuffer> idx_buff;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<OrthoCamera> camera;
	};
}
