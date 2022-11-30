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
#include "ImGameWindow.h"

class ImGuiSamples
{

public: 

	static void Init();

	static void NewFrame(float dt);

	static void Render(float dt);

	static void CleanUp();

public:
	
	static Application* App;
	static ImGuiIO* id;


	static ImHierarchyWindow* ImH;
	static ImInspectorWindow* ImI;

	
};

