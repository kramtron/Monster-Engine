#pragma once
#include "S_GameObject.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "R_Console.h"


#include "R_Mesh.h"
#include "T_MeshLoader.h"
#include "T_TextureLoader.h"

#include <map>

class GameObject;

using namespace std;

//class ImHierarchyWindow;

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


	int AddGameObject(GameObject* gO);

	map<uint, GameObject*> gameObjects;

	

	ImVec4 clear_color = ImVec4(0.9f, 0.0f, 0.0f, 0.9f);
	ImVec4 back_window_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	Color color;

	vec3 aPos;

	bool wireFrame = false;

	int IDCounter = 0;

	bool exit = false;


	uint textureID=0;
private:

	

};