#pragma once
#include "Globals.h"
#include "MathGeoLib.h"
#include "CamBuffers.h"
#include "Application.h"


class CameraClass
{
public:

	CameraClass();
	~CameraClass();


	void Look(const float3& Position, const float3& Reference, bool RotateAroundReference = false);
	void LookAt(const float3& toLookAt);
	void Move(const float3& Movement);


	float* GetViewMatrix();
	float* GetProjMatrix();

	void StartCamBuffer(int width, int height);


	void ChangeToGameCamera();


public:

	float3 x, y, z;
	float3 pos, ref;
	float4x4 viewMatrix, viewMatrixInverse, projMatrix;



	bool gameCamera = false;

	Frustum frustumCamera;
	CamBuffers camBuffer;
	float fieldOfView;

	Application* app;

};

