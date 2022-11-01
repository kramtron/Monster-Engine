#pragma once
#include "S_Component.h"


//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


//class Component;

class GameObject;

class C_Mesh : public Component
{
public:


	C_Mesh(GameObject* gO);
	~C_Mesh();

	void InspectorW() override;



public:

	bool active = false;


};

