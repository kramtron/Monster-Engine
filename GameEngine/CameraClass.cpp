#include "CameraClass.h"

CameraClass::CameraClass()
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::Look(const float3& position, const float3& reference, bool rotateAroundReference)
{
}

void CameraClass::LookAt(const float3& pos)
{

	frustumCamera.front = (pos - frustumCamera.pos).Normalized();

	x = Cross(float3(0.0f, 1.0f, 0.0f), frustumCamera.front).Normalized();
	frustumCamera.up = Cross(frustumCamera.front, x);

}

void CameraClass::Move(const float3& mov)
{
	frustumCamera.pos += mov;
}

float* CameraClass::GetViewMatrix()
{

	float4x4 tempMatrixView = frustumCamera.ViewMatrix();
	tempMatrixView.Transpose();
	return &tempMatrixView.v[0][0];
}

float* CameraClass::GetProjMatrix()
{

	float4x4 tempMatrixProj = frustumCamera.ProjectionMatrix();
	tempMatrixProj.Transpose();
	return &tempMatrixProj.v[0][0];
}

void CameraClass::StartCamBuffer(int width, int height)
{
	camBuffer.StartCamBuffers(width, height);
}

void CameraClass::ChangeToGameCamera()
{
}
