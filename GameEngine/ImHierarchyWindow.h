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

	uint DrawGameObject(GameObject* gO);



	//Colocar lo de aqui en un modulo aparte GameObjectTree module or class?

	uint AddGameObject(GameObject* gameObject);

	void StartGameObject(GameObject* gO, int interations);

public:

	map<uint, GameObject*> gameObjects;

	GameObject* rootGO = nullptr;

	uint IDCounter = 1;

	void SetGameObjectSelected(GameObject* gO);
	GameObject* GetGameObjectSeldcted() { return gameObjectSelected; }

	GameObject* gameObjectSelected = nullptr;

public:

	bool popedUp = false;

	ImGuiTreeNodeFlags baseFlags;


private:
	GameObject* gameObjectDragging = nullptr;
	GameObject* gameObjectRightClick = nullptr;
};

