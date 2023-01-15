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


class GameObject;

class ImHierarchyWindow : public ImMainWindow
{

public:
	ImHierarchyWindow();

	~ImHierarchyWindow();

	static void Update(ImHierarchyWindow* ImH);

	bool isEnable;

	uint DrawGameObject(GameObject* gO);


	void ResetChilds(GameObject* gO);
	void RotateChilds(GameObject* gO);
	//Colocar lo de aqui en un modulo aparte GameObjectTree module or class?


	void StartGameObject(GameObject* gO, int interations);

public:



	GameObject* rootGO = nullptr;

	uint IDCounter = 1;

	void SetGameObjectSelected(GameObject* gO);

	void DrawGameObjectsChilds(GameObject* gO, bool childOnly = false);

	GameObject* GetGameObjectSeldcted() { return gameObjectSelected; }

	GameObject* gameObjectSelected = nullptr;

public:

	bool popedUp = false;

	GameObject* rootGameObject = nullptr;

	static Application* App;


	map<uint, GameObject*>* referenceGameObject;

private:
	GameObject* gameObjectDragging = nullptr;
	GameObject* gameObjectRightClick = nullptr;
	ImGuiTreeNodeFlags baseFlags;


};

