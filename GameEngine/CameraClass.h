#pragma once

#include "MathGeoLib.h"
#include "CamBuffers.h"


class CameraClass
{
public:

	CameraClass();
	~CameraClass();

	void CleanUp();

	void StartCamBuffer(int width, int height);


	float4x4 GetViewMatrix();

	float4x4 GetProjectionMatrix();

	void LookAt(const float3& Spot);

public:

	float3 x, y, z;
	float3 pos, ref;
	float4x4 viewMatrix, viewMatrixInverse, projMatrix;



	bool gameCameraera = false;

	Frustum frustumCamera;
	CamBuffers cameraBuffer;
	float fieldOfView = 60;

	//Application* app;

};

