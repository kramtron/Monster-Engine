#pragma once
#include "glmath.h"
#include "MathGeoLib.h"
#include "S_Component.h"

//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


//class Component;

class GameObject;

class C_Transform : public Component
{

public:
	
	C_Transform(GameObject* gO);
	~C_Transform();



	void TransformToUpdate();



	void InspectorW() override;

	mat4x4 GetGlobalT() const { return transpose(matrix); }


	const vec3 GetPosition() { 
		
		return position; };

	void ResetTransform();




public:



	float3 globalPosition;

	float3 parentGlobalPosition;
	float3 localPosition;

	//C_Transform* GetDescendingTransforms(C_Transform* node, std::vector<C_Transform*>&transform);


public:


	

	float4x4 localTransform;
	float4x4 globalTransform;


	float4x4 globalTransformT;

	mat4x4 matrix;

	/*float3 position;
	float3 scale;
	float3 eRotation;
	Quat rotation;*/


	vec3 position;
	vec3 rotation;
	vec3 scale;

	




};

