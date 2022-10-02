#pragma once
#include "glew.h"

#include "SDL_opengl.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>

typedef unsigned int uint;

class M_Mesh 
{

public:

	M_Mesh();
	~M_Mesh();


	static void meshRenderer();


public:

	uint num_indices = 0;
	uint* indices = nullptr;

	uint num_vertices = 0;
	float* vertices = nullptr;


};
