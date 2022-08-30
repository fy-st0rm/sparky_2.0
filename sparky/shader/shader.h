#pragma once
#include "dependency.h"
#include "../core/core.h"

// Default Shader of Sparky
static std::string SPARKY_DEFAULT_VERT_SHADER = "#version 460 core\n"
"\n"
"layout(location = 0) in vec4 in_position;\n"
"layout(location = 1) in vec4 in_color;\n"
"\n"
"uniform mat4 mvp;\n"
"out vec4 out_color;\n"
"void main()\n"
"{\n"
"	out_color = in_color;\n"
"	gl_Position = in_position;\n"
"};\n";


static std::string SPARKY_DEFAULT_FRAG_SHADER = "#version 460 core\n"
"layout(location = 0) out vec4 color;\n"
"\n"
"in vec4  out_color;\n"
"\n"
"void main()\n"
"{\n"
"	color = out_color;\n"
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

private:
	unsigned int compile_shader(unsigned int type, const std::string& shader);

private:
	unsigned int shader_id;
};
