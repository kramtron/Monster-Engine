#pragma once

#include <string>

//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


using namespace std;
class ImMainWindow
{
public:

	ImMainWindow() {};

	virtual ~ImMainWindow() {};

	void Update() {};

	string windowName = "DefaultWindow";

	//bool isEnable = true;


};

