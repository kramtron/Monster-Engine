#pragma once
#include "S_Component.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "CameraClass.h"

class GameObject;
class C_Camera : public Component
{
public:
	C_Camera(GameObject* gO);
	~C_Camera();


	void InspectorW() override;

public:


	GameObject* gameObjectX;

	//Camara de game
	CameraClass* gameCamera = nullptr;
};

