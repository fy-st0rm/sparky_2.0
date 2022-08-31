#include "texture.h"

namespace Sparky {
	Texture::Texture(const std::string& file_path)
	{
		// Loading the texture
		SDL_Surface* surface = (SDL_Surface*) SPGuard::sdl_check_ptr(IMG_Load(file_path.c_str()));
		this->flip_surface(surface);
	
		this->width  = surface->w;
		this->height = surface->h;
	
		// Binding the texture
		GLCall(glGenTextures(1, &this->texture_id));
		GLCall(glBindTexture(GL_TEXTURE_2D, this->texture_id));
	
		// Setting up some basic modes to display texture
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	
		// Sending the pixel data to opengl
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
		SDL_FreeSurface(surface);
	}
	
	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &this->texture_id));
	}
	
	void Texture::flip_surface(SDL_Surface* surface) 
	{
		SDL_LockSurface(surface);
		
		int pitch = surface->pitch; // row size
		char temp[pitch];
		char* pixels = (char*) surface->pixels;
		
		for(int i = 0; i < surface->h / 2; ++i) {
			// get pointers to the two rows to swap
			char* row1 = pixels + i * pitch;
			char* row2 = pixels + (surface->h - i - 1) * pitch;
			
			// swap rows
			memcpy(temp, row1, pitch);
			memcpy(row1, row2, pitch);
			memcpy(row2, temp, pitch);
		}
		SDL_UnlockSurface(surface);
	}
}
