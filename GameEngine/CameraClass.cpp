#include "CameraClass.h"
#include "Globals.h"
#include "R_mesh.h"
CameraClass::CameraClass()
{

	x = float3(1.0f, 0.0f, 0.0f);
	y = float3(0.0f, 1.0f, 0.0f);
	z = float3(0.0f, 0.0f, 1.0f);

	this->pos = float3(0.0f, 0.0f, 0.0f);
	this->ref = float3(0.0f, 0.0f, 0.0f);


	//Mal orden = No va
	frustumCamera.type = FrustumType::PerspectiveFrustum;
	frustumCamera.verticalFov = DegToRad(60.0);
	frustumCamera.horizontalFov = 2.0f * atanf(tanf(frustumCamera.verticalFov / 2.0f) * 1.77f);
	frustumCamera.farPlaneDistance = 600.0f;
	frustumCamera.nearPlaneDistance = 0.01f;
	frustumCamera.front = z;
	frustumCamera.up = y;

	frustumCamera.pos = this->pos;

	//StartCamBuffer(SCREEN_WIDTH,SCREEN_HEIGHT);

}

CameraClass::~CameraClass()
{
}

void CameraClass::CleanUp()
{

	cameraBuffer.CleanUp();
	//Something more?

}


void CameraClass::StartCamBuffer(int width, int height)
{
	cameraBuffer.StartCamBuffers(width, height);
}

float4x4 CameraClass::GetViewMatrix()
{
	viewMatrix = frustumCamera.ViewMatrix();

	//No this no work
	viewMatrix.Transpose();
	return viewMatrix;
}

float4x4 CameraClass::GetProjectionMatrix()
{
	projMatrix = frustumCamera.ProjectionMatrix().Transposed();
	return projMatrix;
}

void CameraClass::LookAt(const float3& Spot)
{

	ref = Spot;


	//Voy a cometer crimenes de guerra como esto no funcione
	frustumCamera.front = (Spot -frustumCamera.pos).Normalized();
	float3 x = float3(0.0f, 1.0f, 0.0f).Cross(frustumCamera.front).Normalized();
	frustumCamera.up = frustumCamera.front.Cross(x);

}

bool CameraClass::FrustumChecker(M_Mesh* mesh)
{

	float3 tempPoints[8];
	Plane tempFrustumPlanes[6];


	mesh->global_AABB.GetCornerPoints(tempPoints);
	frustumCamera.GetPlanes(tempFrustumPlanes);

	for (size_t i = 0; i < 6; i++)
	{
		int tempInt = 0;

		for (size_t j = 0; j < 8; j++)
		{
			if (tempFrustumPlanes[i].IsOnPositiveSide(tempPoints[j]))
				tempInt++;
		}

		if (tempInt == 8) {
			return false;
		}
	}

	return true;


	return false;
}
