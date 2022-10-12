#pragma once
#include "dependency.h"
#include "../camera/ortho_cam.h"

namespace Sparky {
	class Util
	{
	public:
		static glm::vec2 get_mouse_pos(std::shared_ptr<OrthoCamera> camera)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
	
			// Getting window width and height
			int w, h;
			SDL_Window* sdl_window = SDL_GL_GetCurrentWindow();
			SDL_GetWindowSize(sdl_window, &w, &h);
	
			// Reversing the `y-axis` of SDL to Opengl (+y = down & -y = up) => (+y = up & -y = down)
			y = h - y;
	
			// Getting camera width and height
			float cam_w, cam_h;
			cam_w = camera->get_width();
			cam_h = camera->get_height();
	
			// Calculating ratio of window size and camera size
			float ratio_x = w / cam_w;
			float ratio_y = h / cam_h;
	
			// Creating new position according to the camera size
			int new_x, new_y;
			new_x = x / ratio_x;
			new_y = y / ratio_y;
	
			// Making mouse position relative to the camera
			glm::vec3 cam_pos = camera->get_position();
			new_x += cam_pos.x;
			new_y += cam_pos.y;

			return glm::vec2(new_x, new_y);
		}
	};
}
