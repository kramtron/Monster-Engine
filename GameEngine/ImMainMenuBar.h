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

	static void ThemeStyleChanger();
	

public:

	static bool isEnable;

	static int colorStyle;
	static bool styleSelectD;
	static bool styleSelectL;
	static bool styleSelectSD;
	static bool styleSelectP;

	static float colorWind[4];
	static float colorText[4];


	
};

