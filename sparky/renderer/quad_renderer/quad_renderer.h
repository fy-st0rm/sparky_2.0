#pragma once
#include "../../buffers/buffers.h"
#include "../../shader/shader.h"
#include "../../texture/texture.h"
#include "../vertex.h"

namespace Sparky {
	class QuadRenderer
	{
	public:
		QuadRenderer(int max_quad_cnt, std::shared_ptr<Shader> shader);
		~QuadRenderer();
	
	public:
		// Render functions
		void render_begin();
		void render_end();
	
		Quad create_quad(glm::vec3 pos, glm::vec2 size, glm::vec4 color, glm::vec4 tex_cord, const Texture& texture);
		void push_quad(const Quad& quad);
		void print_buffer();

	public:
		// Getters and setters
		std::shared_ptr<Shader> get_shader() const { return this->shader; }
	
	public:
		void generate_default_texture();
		void bind_all_textures();
		void provide_texture_samplers();
	
	private:
		int max_quad_cnt;
		int max_idx_cnt;
		int max_buff_size;
	
		// Vertices buffer
		int buff_idx;
		float* buffer;
	
		// Texture buffer
		std::vector<float> texture_slots;
	
	private:
		std::shared_ptr<VertexArray> vert_array;
		std::shared_ptr<VertexBuffer> vert_buff;
		std::shared_ptr<IndexBuffer> idx_buff;
		std::shared_ptr<Shader> shader;
	};
}
