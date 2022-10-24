#pragma once
#include "ImMainWindow.h"

#include "Application.h"
#include "SDL_opengl.h"


//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "S_GameObject.h"

#include <map>

class ImHierarchyWindow : public ImMainWindow
{

public:
	ImHierarchyWindow();

	~ImHierarchyWindow();

	static void Update();

	static bool isEnable;

	void DrawGameObject(GameObject* gameObject);



	//Colocar lo de aqui en un modulo aparte


	uint AddGameObject(GameObject* gameObject);
public:

	map<uint, GameObject*> gameObjects;

	GameObject* rootGO = nullptr;

	uint IDCounter = 1;

public:

	bool popedUp = false;



};

