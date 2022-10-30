#pragma once
#include "Application.h"


#include "SDL_opengl.h"
#include "Primitive.h"
#include "glew.h"

#include <gl/GL.h>
#include <gl/GLU.h>


#include "ilu.h"
#include "il.h"
#include "ilut.h"

#include <string>

#define HEIGHT 64
#define WIDTH 64


typedef unsigned int uint;

using namespace std;

enum class TextureTypes {

	NONE,
	CHECKERS,
	CURRENT,
};

class TextureLoader
{

public:

	static void ImportTexture(std::string& filePath, uint size, char* buffer);

	static uint LoadTexture(const char* filePath);

	static void Init();
	static void Start();
	static void CleanUp();

private:

	GLubyte checkImage[HEIGHT][WIDTH][4]; // height width rgba

};