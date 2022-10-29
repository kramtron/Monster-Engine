#pragma once


#include "glew.h"
//#include "Application.h" //Por algun motivo que no entiendo al colocar esto aquí salta error de class undefined

#include "SDL_opengl.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>


#include <vector>

using namespace std;
typedef unsigned int uint;

#define VERTEX_ARG 5

enum class TextureTypes;
class C_Transform;
class M_Mesh
{

public:

		M_Mesh();
		~M_Mesh();
		

	void meshRenderer(const float* globalT, TextureTypes textureT);


public:

		uint num_indices = 0;
		uint* indices = nullptr;

		uint num_vertices = 0;
		float* vertices = nullptr;

		static vector<M_Mesh*> meshes;

		uint id_vertices = 0;
		uint id_indices = 0;


		uint textureID = 0;
};
