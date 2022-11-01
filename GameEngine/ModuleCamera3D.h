#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"


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

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

	//Funcionts to draw
	void Draw();
	void StopDraw();

	//void LookAt(const vec3& pos);


private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;

	StatesOfCam stateOfCam=NORMAL;
	ImHierarchyWindow* ImH;
	GameObject* selectedGameObejct;

	bool center = false;

	vec3 newPos;

	static C_Transform* gOpos;

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;
};