#include "guard.h"

// SDL Error checker
int SPGuard::sdl_check(int result)
{
	if (result < 0) Log::error(SDL_GetError(), SPARKY_NULL);
	return result;
}

void* SPGuard::sdl_check_ptr(void* result)
{
	if (!result) Log::error(SDL_GetError(), SPARKY_NULL);
	return result;
}
