#pragma once
#include "Globals.h"
#include "MathGeoLib.h"
#include "Application.h"

class CamBuffers;

class CameraClass
{
public:

	CameraClass();
	~CameraClass();

	void CleanUp();


	void Look(const float3& Position, const float3& Reference, bool RotateAroundReference = false);
	void LookAt(const float3& toLookAt);
	void Move(const float3& Movement);


	float* GetViewMatrix();
	float* GetProjMatrix();

	void StartCamBuffer(int width, int height);


	void ChangeTogameCameraera();


public:

	float3 x, y, z;
	float3 pos, ref;
	float4x4 viewMatrix, viewMatrixInverse, projMatrix;



	bool gameCameraera = false;

	Frustum frustumCamera;
	CamBuffers cameraBuffer;
	float fieldOfView;

	Application* app;

};

