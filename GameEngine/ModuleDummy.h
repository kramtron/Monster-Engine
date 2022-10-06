#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"


#include "R_Mesh.h"
#include "T_MeshLoader.h"

class ModuleDummy : public Module
{
public:

	ModuleDummy(Application* app, bool start_enabled = true);
	~ModuleDummy();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


	ImVec4 clear_color = ImVec4(0.9f, 0.0f, 0.0f, 0.9f);
	ImVec4 back_window_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	Color color;

	vec3 aPos;

	bool wireFrame = true;
private:

	

};