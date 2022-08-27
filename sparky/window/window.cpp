#include "window.h"

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
	this->window   = (SDL_Window*)   SPGuard::sdl_check_ptr(SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, 0));
	this->renderer = (SDL_Renderer*) SPGuard::sdl_check_ptr(SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED));
}
