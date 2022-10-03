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

	void renderMesh(M_Mesh* meshToRender);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	//ImGui
	ImGuiIO* io;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	M_Mesh* testMesh;

	M_Mesh* arrayMesh[1];
	const aiScene* scene;

	const char* file_path;
};