#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "glmath.h"
#include "Light.h"

#include "R_Mesh.h"
#include "T_MeshLoader.h"
//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "CameraClass.h"
#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void BindCamerBuffers(CameraClass* cc);

	void RenderMeshes();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	

	uint framebuffer=0;
	uint textureColorbuffer;
	uint rbo;
	
	vector<M_Mesh*> rMeshes;

	const char* file_path;
private: 
	bool firstDone = false;
};