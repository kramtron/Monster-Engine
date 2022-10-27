#pragma once
#include "ImMainWindow.h"
#include "Application.h"
#include "ImHierarchyWindow.h"

class ImHierarchyWindow;

class ImMainMenuBar : ImMainWindow
{
public:

	ImMainMenuBar();
	~ImMainMenuBar();
	static void Update(Application* App, ImHierarchyWindow* imH);

	static bool isEnable;

	
};

