#include "shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(this->shader_id));
}

void Shader::bind()
{
	GLCall(glUseProgram(this->shader_id));
}

void Shader::unbind()
{
	GLCall(glUseProgram(0));
}

void Shader::load_shader_from_string(const std::string& vert_shader, const std::string& frag_shader)
{
	this->shader_id = glCreateProgram();

	// Compiling vertex and fragment shader
	unsigned int vs = this->compile_shader(GL_VERTEX_SHADER, vert_shader);
	unsigned int fs = this->compile_shader(GL_FRAGMENT_SHADER, frag_shader);

	// Attaching shader
	GLCall(glAttachShader(this->shader_id, vs));
	GLCall(glAttachShader(this->shader_id, fs));
	GLCall(glLinkProgram(this->shader_id));
	GLCall(glValidateProgram(this->shader_id));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& shader)
{
	unsigned int id = glCreateShader(type);
	const char* src = shader.c_str();
	GLCall(glShaderSource(id, 1, &src, NULL));
	GLCall(glCompileShader(id));

	// checking error in shader
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*) calloc(length, sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));

		// Priting the error
		char msg[1000];
		sprintf(msg, "Failed to compile [%s shader]\n%s", (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), message);
		Log::error(std::string(msg), SPARKY_NULL);

		free(message);

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;

}
