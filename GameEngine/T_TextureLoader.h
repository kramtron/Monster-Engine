#pragma once
#include "glew.h"

#include "SDL_opengl.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ilu.h"
#include "il.h"
typedef unsigned int uint;


class TextureLoader
{
	uint LoadToMemory(char* buffer, int size, int* width = nullptr, int* height = nullptr);
};