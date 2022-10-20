#pragma once
#include "ImMainWindow.h"

#include "Application.h"
#include "SDL_opengl.h"


//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


class ImHierarchyWindow : public ImMainWindow
{

public:
	ImHierarchyWindow();

	~ImHierarchyWindow();

	static void Update();

	static bool isEnable;

};

