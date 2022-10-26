#pragma once
#include "ImMainWindow.h"
#include "Application.h"

class ImMainMenuBar : ImMainWindow
{
public:

	ImMainMenuBar();
	~ImMainMenuBar();
	static void Update(Application* App);

	static bool isEnable;

};

