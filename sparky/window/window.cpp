#include "window.h"

namespace Sparky {
	Window::Window(const std::string& title, int width, int height)
		:title(title), width(width), height(height)
	{
		init_sdl();
		this->closed = false;
	}
	
	Window::~Window()
	{
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
	}
	
	void Window::init_sdl()
	{
		SPGuard::sdl_check(SDL_Init(SDL_INIT_EVERYTHING));
		SPGuard::sdl_check(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG));
	
		// Setting some attributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
		// Creating SDL window and renderer
		this->window   = (SDL_Window*)   SPGuard::sdl_check_ptr(SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL));
		this->renderer = (SDL_Renderer*) SPGuard::sdl_check_ptr(SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED));
	
		SPGuard::sdl_check_ptr(SDL_GL_CreateContext(this->window));
	
		if (glewInit() != GLEW_OK)
			Log::error("[Error]: Failed to initialize glew", SPARKY_NULL);
	
		// Setting up alpha channels and blendings
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}
	
	void Window::clear(glm::vec4 color)
	{
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	
	void Window::update()
	{
		SDL_GL_SwapWindow(this->window);
	}
}
