#pragma once
#include "dependency.h"
#include "../core/core.h"

namespace Sparky {

	// Default Shader of Sparky
	static std::string SPARKY_DEFAULT_VERT_SHADER = "#version 460 core\n"
	"\n"
	"layout(location = 0) in vec4  in_position;\n"
	"layout(location = 1) in vec4  in_color;\n"
	"layout(location = 2) in vec2  in_tex_cord;\n"
	"layout(location = 3) in float in_tex_id;\n"
	"\n"
	"uniform mat4 mvp;\n"
	"out vec4  out_color;\n"
	"out vec2  out_tex_cord;\n"
	"out float out_tex_id;\n"
	"void main()\n"
	"{\n"
	"	out_color = in_color;\n"
	"	out_tex_cord = in_tex_cord;\n"
	"	out_tex_id = in_tex_id;\n"
	"	gl_Position = mvp * in_position;\n"
	"};\n";

	static std::string SPARKY_DEFAULT_FRAG_SHADER = "#version 460 core\n"
	"layout(location = 0) out vec4 color;\n"
	"\n"
	"in vec4  out_color;\n"
	"in vec2  out_tex_cord;\n "
	"in float out_tex_id;\n"
	"\n"
	"uniform sampler2D textures[32];\n"
	"\n"
	"void main()\n"
	"{\n"
	"	int index = int(out_tex_id);\n"
	"	color = texture(textures[index], out_tex_cord) * out_color;\n"
	"};\n";
	
	
	class Shader
	{
	public:
		Shader();
		~Shader();
	
	public:
		void load_shader_from_string(const std::string& vert_shader, const std::string& frag_shader);
	
		void bind();
		void unbind();
	
	public:
		unsigned int get_shader_id() const { return this->shader_id; }
		int get_uniform_location(const std::string& name);
	
	private:
		unsigned int compile_shader(unsigned int type, const std::string& shader);
	
	private:
		unsigned int shader_id;
		std::unordered_map<std::string, int> uniform_locations;
	};
}
