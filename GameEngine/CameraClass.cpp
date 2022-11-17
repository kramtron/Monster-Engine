#include "CameraClass.h"

CameraClass::CameraClass()
{

	x = float3(1.0f, 0.0f, 0.0f);
	y = float3(0.0f, 1.0f, 0.0f);
	z = float3(0.0f, 0.0f, 1.0f);



	//Mal orden = No va
	frustumCamera.type = FrustumType::PerspectiveFrustum;
	frustumCamera.verticalFov = DegToRad(fieldOfView);
	frustumCamera.horizontalFov = 2.0f * atanf(tanf(frustumCamera.verticalFov / 2.0f) * 1.77f);
	frustumCamera.farPlaneDistance = 600.0f;
	frustumCamera.nearPlaneDistance = 0.01f;
	frustumCamera.front = z;
	frustumCamera.up = y;
	this->pos = float3(0.0f, 0.0f, 0.0f);
	this->ref = float3(0.0f, 0.0f, 0.0f);
	frustumCamera.pos = this->pos;


}

CameraClass::~CameraClass()
{
}

void CameraClass::Look(const float3& position, const float3& reference, bool rotateAroundReference)
{
	this->pos = position;
	this->ref = reference;

	frustumCamera.front = (pos - ref).Normalized();
	frustumCamera.up = Cross(frustumCamera.front, x);
	if (!rotateAroundReference) {
		this->ref = this->pos;
		this->pos += z * 0.05;
	}

	//CalculateViewMatrix();

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
	//:(
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

	app = Application::GetInstance();

	if (app->camera->gameCam != nullptr) {

		//Lista de gamecams?
	}
}
