#include "shader.h"

namespace Sparky {
	Shader::Shader()
		:shader_id(0)
	{
		this->load_shader_from_string(SPARKY_DEFAULT_VERT_SHADER, SPARKY_DEFAULT_FRAG_SHADER);
		this->bind();
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
		if (this->shader_id) 
			GLCall(glDeleteProgram(this->shader_id));

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

	void Shader::load_shader_from_file(const std::string& vert_shader_file, const std::string& frag_shader_file)
	{
		std::stringstream vert_str_stream, frag_str_stream;
		std::string       vert_shader, frag_shader;
		std::string line;

		// Reading vertex shader
		std::ifstream vert_stream(vert_shader_file);
		while (std::getline(vert_stream, line))
			vert_str_stream << line << "\n";

		// Reading fragment shader
		std::ifstream frag_stream(frag_shader_file);
		while (std::getline(frag_stream, line))
			frag_str_stream << line << "\n";

		vert_shader = vert_str_stream.str();
		frag_shader = frag_str_stream.str();

		load_shader_from_string(vert_shader, frag_shader);
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
	
	int Shader::get_uniform_location(const std::string& name)
	{
		if (this->uniform_locations.find(name) != this->uniform_locations.end())
			return this->uniform_locations[name];
	
		int loc = glGetUniformLocation(this->get_shader_id(), name.c_str());
		if (loc == -1)
			Log::error("Cannot find uniform `" + name + "` in the shader.\n", SPARKY_NULL);
	
		this->uniform_locations[name] = loc;
		return loc;
	}
}
