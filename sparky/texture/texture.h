#pragma once
#include "dependency.h"
#include "../core/core.h"

// TODO: Do something for JPEG file format because it causes a crash `glTexImage2D` in this function

namespace Sparky {
	class Texture
	{
	public:
		Texture(const std::string& file_path);
		Texture(): texture_id(SparkyWhiteTextureID) {};
		~Texture();
	
	public:
		// Loaders
		void load_from_sdl_surface(SDL_Surface* surface);
	
		
		// Getters
		unsigned int get_texture_id() const { return this->texture_id; }
		int get_width()  const { return this->width; }
		int get_height() const { return this->height; }

	private:
		void flip_surface(SDL_Surface* surface);
		unsigned int get_color_format(SDL_Surface* surface);
		void pack_surface(SDL_Surface* surface);
	
	private:
		unsigned int texture_id = 0;
		int width, height;
	};
}
