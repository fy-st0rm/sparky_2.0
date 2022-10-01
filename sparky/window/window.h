#pragma once
#include "dependency.h"
#include "../core/core.h"

namespace Sparky {
	// Sparky Engine window class
	class Window
	{
	public:
		Window(const std::string& title, int width, int height, int flag);
		~Window();
	
	public:
		void clear(glm::vec4 color);
		void update();
		void auto_resize_viewport();
		void resize_viewport(int width, int height);
	
	public:
		// Setters
		inline void destroy()   { this->closed = true; }
	
		// Getters
		inline int get_width()  const { return this->width;  }
		inline int get_height() const { return this->height; }
	
		inline bool is_closed() const { return this->closed; }

		SDL_Window* get_sdl_window() const { return this->window; }
		SDL_GLContext get_gl_context() const { return this->gl_context; }
	
	private:
		void init_sdl();
	
	private:
		int width, height;
		std::string title;
		bool closed;
		int flag;
	
	private:
		SDL_Window*   window;
		SDL_Renderer* renderer;
		SDL_GLContext gl_context;
	};
}
