#pragma once
#include "dependency.h"
#include "../core/core.h"

// Sparky Engine window class
class Window
{
public:
	Window(const std::string& title, int width, int height);
	~Window();

public:
	// Setters
	inline void destroy()   { this->closed = true; }

	// Getters
	inline int get_width()  const { return this->width;  }
	inline int get_height() const { return this->height; }

	inline bool is_closed() const { return this->closed; }

private:
	void init_sdl();

private:
	int width, height;
	std::string title;
	bool closed;

private:
	SDL_Window*   window;
	SDL_Renderer* renderer;
};
