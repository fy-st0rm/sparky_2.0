#pragma once
#include "log.h"

// Macros to handle opengl errors
#define SP_ASSERT(x) if (!(x)) exit(1);
#define GLCall(x) Sparky::SPGuard::clear_error(); \
x;\
SP_ASSERT(Sparky::SPGuard::error_log(#x, __FILE__, __LINE__))

namespace Sparky {
	// Class for error handling
	class SPGuard
	{
	public:
		// SDL Error checker
		static int sdl_check(int result);
		static void* sdl_check_ptr(void* result);
	
		// Opengl error checker
		static void clear_error()
		{
			while (glGetError());
		}
	
		static bool error_log(const char* function, const char* file, int line)
		{
			GLenum error;
			while (error = glGetError())
			{
				Log::warning("[Error code]: " + std::to_string(error), SPARKY_NULL);
				Log::error("[Opengl error]: " + std::string(function) + " " +  file + " " + std::to_string(line), SPARKY_NULL);
				return false;
			}
			return true;
		}
	};
}
