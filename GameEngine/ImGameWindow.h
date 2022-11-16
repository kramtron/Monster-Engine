#pragma once
#include "ImMainWindow.h"

#include "Application.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


class ImGameWindow : public ImMainWindow
{

public:

	ImGameWindow();

	~ImGameWindow();

	static void Update(Application* App);

	static bool isEnable;

};

