#pragma once
#include "ImMainWindow.h"


#include "Application.h"
#include "SDL_opengl.h"


//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "ImHierarchyWindow.h"

class ImInspectorWindow : public ImMainWindow
{
public:

	ImInspectorWindow();

	~ImInspectorWindow();

	static void Update(ImHierarchyWindow* ImH, ImInspectorWindow* ImI);

	static bool isEnable;

	void GameObjectSelected(GameObject* g) { gameObjectSelected = g; };

	GameObject* gameObjectSelected = nullptr;

};

