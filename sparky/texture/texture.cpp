#include "texture.h"

namespace Sparky {
	Texture::Texture(const std::string& file_path)
	{
		// Loading the texture
		SDL_Surface* surface = (SDL_Surface*) SPGuard::sdl_check_ptr(IMG_Load(file_path.c_str()));
		this->load_from_sdl_surface(surface);
	}
	
	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &this->texture_id));
	}

	void Texture::load_from_sdl_surface(SDL_Surface* surface)
	{
		this->width  = surface->w;
		this->height = surface->h;

		// Adjusting the SDL_Surface
		this->flip_surface(surface);
		this->pack_surface(surface);
		unsigned int format = this->get_color_format(surface);

		// Deleting old texture if exists
		if (this->texture_id != 0)
		{
			GLCall(glDeleteTextures(1, &this->texture_id));
		}
	
		// Binding the texture
		GLCall(glGenTextures(1, &this->texture_id));
		GLCall(glBindTexture(GL_TEXTURE_2D, this->texture_id));
	
		// Setting up some basic modes to display texture
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	
		// Sending the pixel data to opengl
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, surface->pixels));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
		SDL_FreeSurface(surface);
	}
	
	void Texture::flip_surface(SDL_Surface* surface) 
	{
		// Flips SDL_Surface upside down
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

	unsigned int Texture::get_color_format(SDL_Surface* surface)
	{
		// Gets the surface format for the texture
		unsigned int colors = surface->format->BytesPerPixel;
		unsigned int format;
		if (colors == 4) {   // alpha
			if (surface->format->Rmask == 0x000000ff)
				format = GL_RGBA;
			else
				format = GL_BGRA;
		} else {             // no alpha
			if (surface->format->Rmask == 0x000000ff)
				format = GL_RGB;
			else
				format = GL_BGR;
		}
		return format;
	}
	
	void Texture::pack_surface(SDL_Surface* surface)
	{
		// Packs the surface and makes the pitch same as width (reference: https://discourse.libsdl.org/t/sdl-ttf-2-0-18-surface-to-opengl-texture-not-consistent-with-ttf-2-0-15/34529/5)
		Sint32 i;
		Uint32 len = surface->w * surface->format->BytesPerPixel;
		Uint8 *src = (Uint8*) surface->pixels;
		Uint8 *dst = (Uint8*) surface->pixels;
		for (i = 0; i < surface->h; i++) {
			SDL_memmove(dst, src, len);
			dst += len; 
			src += surface->pitch;
		}
		surface->pitch = len;
	}
}
