#include "CameraClass.h"
#include "Globals.h"
CameraClass::CameraClass()
{

	x = float3(1.0f, 0.0f, 0.0f);
	y = float3(0.0f, 1.0f, 0.0f);
	z = float3(0.0f, 0.0f, 1.0f);

	this->pos = float3(0.0f, 0.0f, 0.0f);
	this->ref = float3(0.0f, 0.0f, 0.0f);


	//Mal orden = No va
	frustumCamera.type = FrustumType::PerspectiveFrustum;
	frustumCamera.verticalFov = DegToRad(fieldOfView);
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

float* CameraClass::GetViewMatrix()
{
	viewMatrix = frustumCamera.ViewMatrix();

	//No this no work
	viewMatrix.Transpose();
	return viewMatrix.ptr();
}

float* CameraClass::GetProjectionMatrix()
{
	projMatrix = frustumCamera.ProjectionMatrix();
	projMatrix.Transpose();
	return projMatrix.ptr();
}
