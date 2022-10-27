#pragma once
#include "glew.h"
#include "Application.h"

#include "SDL_opengl.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ilu.h"
#include "il.h"

#include <string>


typedef unsigned int uint;

using namespace std;
class TextureLoader
{

public:

	static void ImportTexture(std::string& filePath, uint size, char* buffer);

	static uint LoadTexture(std::string&& filePath, uint size, uint* w, uint* h);





};