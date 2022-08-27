#pragma once
#include "log.h"

class SPGuard
{
public:
	// SDL Error checker
	static int sdl_check(int result);
	static void* sdl_check_ptr(void* result);
};
