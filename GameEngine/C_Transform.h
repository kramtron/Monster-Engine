#pragma once
#include "MathGeoLib.h"
#include "S_Component.h"

//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


class Component;
class GameObject;

class C_Transform : public Component
{

public:
	
	C_Transform(GameObject* gO);
	~C_Transform();

	void InspectorW() override;

public:

	

	/*float4x4 localTransform;
	float4x4 globalTransform;*/


	float3 position;
	float3 scale;
	float3 rotation;



};

