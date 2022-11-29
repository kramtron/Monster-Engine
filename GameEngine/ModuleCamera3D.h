#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "CameraClass.h"


//class CameraClass;

class C_Transform;

enum StatesOfCam {

	LOOKINGAT,
	FLYING,
	NORMAL,
};
class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const float3 &, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3 &Spot);
	void Move(const float3 &Movement);
	float* GetViewMatrix();

	//Funcionts to draw
	void Draw();
	void StopDraw();

	//void LookAt(const float3& pos);

	float* GetProjMatrix();

private:

	void CalculateViewMatrix();

public:
	
	float3 X, Y, Z, Position, Reference;

	float lenght;
	float4x4 rmat;
	/*float3 x, y, z;
	float3 pos, ref;*/
	float4x4 viewMatrix, viewMatrixInverse, projMatrix;

	StatesOfCam stateOfCam=NORMAL;
	ImHierarchyWindow* ImH;
	GameObject* selectedGameObejct;

	bool center = false;

	float3 newPos;

	static C_Transform* gOpos;

	//Camara de game
	CameraClass* gameCamera = nullptr;
	//Camara de la escena
	CameraClass* sceneCamera;


private:

	
};