#pragma once


#include "glew.h"
//#include "Application.h" //Por algun motivo que no entiendo al colocar esto aquí salta error de class undefined

#include "SDL_opengl.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>
//#include "glmath.h"
#include "MathGeoLib.h"

#include <vector>

using namespace std;
typedef unsigned int uint;

#define VERTEX_ARG 5

enum class TextureTypes;

class TextureLoader;
class C_Transform;
class M_Mesh
{

public:

		M_Mesh();
		~M_Mesh();
		

	void meshRenderer(float4x4, TextureTypes textureT, float4x4 global);


public:

		uint num_indices = 0;
		uint* indices = nullptr;

		uint num_vertices = 0;
		float* vertices = nullptr;

		static vector<M_Mesh*> meshes;

		uint id_vertices = 0;
		uint id_indices = 0;


		uint textureID = 0;

public: 


	AABB AABB_;
	OBB OBB_;
	AABB global_AABB;

	float3 tempCorn1[8];
	float3 tempCorn2[8];

	void InitAABB();
	void RenderAABB();
	void DrawAABB_Boxes(float3* x, float3 y);

private:
	vector<float3> tempVert;
};
