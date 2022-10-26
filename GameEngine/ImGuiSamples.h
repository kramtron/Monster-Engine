#pragma once
#include "Application.h"
#include "SDL_opengl.h"


//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


#include "ImInspectorWindow.h"
#include "ImHierarchyWindow.h"
#include "ImSceneWindow.h"
#include "ImMainMenuBar.h"

class ImGuiSamples
{

public: 

	static void Init();

	static void NewFrame();

	static void Render();

	static void CleanUp();

public:
	
	static Application* App;
	static ImGuiIO* id;


	static ImHierarchyWindow* ImH;

	
};

