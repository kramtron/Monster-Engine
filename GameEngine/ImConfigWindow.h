#pragma once
#include "ImMainWindow.h"

#include "Application.h"

#include "Globals.h"
using namespace std;

class ImConfigWindow : public ImMainWindow
{
public:
	static void Update(Application* app, float dt);


	static int fpsLimit;


private:


	static vector<float> fpsDebug;
	static vector<float> fpsDebugAux;
	static vector<float> timeDebug;
	static vector<float> timeDebugAux;



	static bool vSync;
	static bool lights;
	static bool depths;
	static bool isCullFaces;
	static bool colorM;
	static bool text2D;
	static bool isFullScreen;
	static bool isRe;
	static bool isBor;

	static float bright;
	static float bright_aux;

};

