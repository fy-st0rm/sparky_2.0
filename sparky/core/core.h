#pragma once

#include "log.h"
#include "guard.h"
#include "uuid.h"

namespace Sparky {
	// Important definations
	#define SparkyEvent SDL_Event
	#define SparkyWindowResizable SDL_WINDOW_RESIZABLE
	#define SparkyWindowFullscreen SDL_WINDOW_FULLSCREEN
	#define SparkyWhiteTextureID 0
	
	// Modes of sparky
	enum modes
	{
		DEBUG_MODE,
		RELEASE_MODE
	};
}
