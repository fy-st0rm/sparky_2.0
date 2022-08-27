#pragma once

// Standard 
#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

// SDL
#include <SDL2/SDL.h>


/*
// Opengl Error handling
#define ASSERT(x) if (!(x)) exit(1);
#define GLCall(x) ClearError(); \
x;\
ASSERT(ErrorLog(#x, __FILE__, __LINE__))

static void ClearError()
{
    while(glGetError());
}

static bool ErrorLog(const char* function, const char* file, int line)
{
	GLenum error;
    while (error = glGetError())
    {
        fprintf(stderr, "[Error code]: %s\n", error);
        fprintf(stderr, "[Opengl error]: %s %s: %d\n", function ,file, line);
        return false;
    }
    return true;
}
*/
