#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "imgui.h"
#include "C_Transform.h"
#include "CameraClass.h"

//#include "MathGeoLib.h"//Need here? If this activated error in float3.h

//Need more includes for sure

#include "ModuleRenderer3D.h"
#include "ImHierarchyWindow.h"
#include "C_Transform.h"

#include "SDL_opengl.h"



C_Transform* ModuleCamera3D::gOpos = nullptr;

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//CalculateViewMatrix();

	

	//newPos = float3(0.0f, 0.0f, 0.0f);

	//sceneCamera = new CameraClass();
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Init()
{
	LOG("Setting up the camera");
	bool ret = true;

	sceneCamera = new CameraClass();
	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");
	delete sceneCamera;
	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	//Arregalar TODO
	Quat direction = Quat::identity;
	sceneCamera->frustumCamera.WorldMatrix().Decompose(float3(), direction, float3());

	newPos = float3(0, 0, 0);
	 

	float speed = 300.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	//Mouse scrolls
	int dx = -App->input->GetMouseXMotion();
	int dy = -App->input->GetMouseYMotion();
	int dw = -App->input->GetMouseZ(); //wheel

	float Sensitivity = speed / 6.0f;
	
	Sensitivity * 100;
	//Look to selected Object
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT || center == true) {

		if (gOpos != nullptr)
			LookAt(gOpos->GetPosition());

	}

	//Camera states
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		stateOfCam = LOOKINGAT;
	}
	else if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {
		stateOfCam = FLYING;
	}
	else {
		stateOfCam = NORMAL;
	}

	switch (stateOfCam) {
	case LOOKINGAT:

			

		if (gOpos != nullptr) {
			LookAt(gOpos->GetPosition());
			//sceneCamera->ref = gOpos->GetPosition();

		}
		else {
			sceneCamera->ref = float3(0.0f, 0.0f, 0.0f);

		}
		 //sceneCamera.pos -= sceneCamera.ref;

		

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			//I hate quats
			Quat x = Quat::identity;
			x.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX * DEGTORAD);
			direction = x * direction;
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity * 10;

			Quat y = Quat::identity;
			y.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaY * DEGTORAD);
			direction =  direction * y;

		}



		/*rmat = sceneCamera->frustumCamera.WorldMatrix();
		rmat.SetRotatePart(direction.Normalized());
		sceneCamera->frustumCamera.SetWorldMatrix(rmat.Float3x4Part());

		sceneCamera->frustumCamera.pos = sceneCamera->ref + (sceneCamera->frustumCamera.front * -(float3(sceneCamera->ref - sceneCamera->frustumCamera.pos).Length()));*/	

		//LOG("camera pos: %d", sceneCamera->frustumCamera.pos.x);

		break;

	case FLYING:
		//sceneCamera->ref =  sceneCamera->pos;
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= sceneCamera->frustumCamera.front * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += sceneCamera->frustumCamera.front * speed;


		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= sceneCamera->frustumCamera.WorldRight() * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += sceneCamera->frustumCamera.WorldRight() * speed;

		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) sceneCamera->frustumCamera.pos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) sceneCamera->frustumCamera.pos.y -= speed;

		// Mouse motion ----------------

		//Quat direction;

		//sceneCamera->frustumCamera.WorldMatrix().Decompose(float3(), direction, float3());

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			//I hate quats
			Quat x = Quat::identity;
			x.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX * DEGTORAD);
			direction = x * direction;
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity * 10;

			Quat y = Quat::identity;
			y.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaY * DEGTORAD);
			direction = direction * y;

		}



		/*rmat = sceneCamera->frustumCamera.WorldMatrix();
		rmat.SetRotatePart(direction.Normalized());
		sceneCamera->frustumCamera.SetWorldMatrix(rmat.Float3x4Part());*/
			

			break;
	case NORMAL:

		//Wheel click
		if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT) {

			/*newPos += X * dx * Sensitivity;
			newPos -= Y * dy * Sensitivity;*/

			//Is WorldRight no worldMat 
			sceneCamera->frustumCamera.pos += sceneCamera->frustumCamera.WorldRight() * (speed * dx / 2);
			sceneCamera->frustumCamera.pos -= sceneCamera->frustumCamera.up * (speed * dy / 2);

		}

		//Wheel Scroll
		if (dw != 0) {
			sceneCamera->frustumCamera.pos += sceneCamera->frustumCamera.front * speed * -dw;

		}

		/*rmat = sceneCamera->frustumCamera.WorldMatrix();
		rmat.SetRotatePart(direction.Normalized());
		sceneCamera->frustumCamera.SetWorldMatrix(rmat.Float3x4Part());*/

		break;
	}

	

	rmat = sceneCamera->frustumCamera.WorldMatrix();
	rmat.SetRotatePart(direction.Normalized());
	sceneCamera->frustumCamera.SetWorldMatrix(rmat.Float3x4Part());

	sceneCamera->frustumCamera.pos = sceneCamera->ref + (sceneCamera->frustumCamera.front * -(float3(sceneCamera->ref - sceneCamera->frustumCamera.pos).Length()));
	

	// Recalculate matrix -------------
	//CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3 &position, const float3 &reference, bool RotateAroundsceneCamera)
{
	sceneCamera->frustumCamera.pos = position;
	sceneCamera->ref = reference;

	LookAt(sceneCamera->ref);
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const float3 &Spot)
{

	sceneCamera->ref = Spot;


	//Voy a cometer crimenes de guerra como esto no funcione
	sceneCamera->frustumCamera.front = (Spot - sceneCamera->frustumCamera.pos).Normalized();
	float3 x = Cross(float3(0.0f, 1.0f, 0.0f), sceneCamera->frustumCamera.front).Normalized();
	sceneCamera->frustumCamera.up = sceneCamera->frustumCamera.front.Cross(x);

	//CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3 &Movement)
{
	 sceneCamera->frustumCamera.pos += Movement;

	//CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{

	viewMatrix = sceneCamera->frustumCamera.ViewMatrix();

	//No this no work
	viewMatrix.Transpose();
	return viewMatrix.ptr();
}

void ModuleCamera3D::Draw()
{

	//Start gl things
	//Disable by default so we have to enable first
		//OpenGl automatically stores things
			//https://learnopengl.com/Advanced-OpenGL/Depth-testing#:~:text=glEnable%20(GL_DEPTH_TEST)%3B,failed%20the%20depth%20test%20accordingly.

	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixf(GetViewMatrix());

	//clear so no update depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
}

void ModuleCamera3D::StopDraw()
{
	glDisable(GL_DEPTH_TEST);
}
float* ModuleCamera3D::GetProjMatrix()
{

	float4x4 tempMatrixProj = sceneCamera->frustumCamera.ProjectionMatrix();
	tempMatrixProj.Transpose();
	return &tempMatrixProj.v[0][0];
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	//ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(sceneCamera.x,  sceneCamera.pos), -dot(sceneCamera.y,  sceneCamera.pos), -dot(sceneCamera.z,  sceneCamera.pos), 1.0f);
	//ViewMatrixInverse = inverse(ViewMatrix);
}