#pragma once
#include "ImMainWindow.h"


#include "Application.h"
#include "SDL_opengl.h"


//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


#include "ImHierarchyWindow.h"

class ImSceneWindow : public ImMainWindow
{
public:
	ImSceneWindow();

	~ImSceneWindow();

	static void Update(Application* App, ImHierarchyWindow* ImH);

	static bool isEnable;

	ImVec2 GetMousePosNormalized(float x, float y, float w, float h, ImVec2 p);

};

