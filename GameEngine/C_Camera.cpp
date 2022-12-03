#include "C_Camera.h"
#include "S_GameObject.h"


C_Camera::C_Camera(GameObject* gO) : Component(gO)
{

	gameObjectX = gO;



}

C_Camera::~C_Camera()
{
}

void C_Camera::InspectorW()
{

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::DragFloat("Near Distance ", &gameCamera->frustumCamera.nearPlaneDistance, 0.1f, 0.01);

		ImGui::DragFloat("Far Distance ", &gameCamera->frustumCamera.farPlaneDistance, 1.0f, 0.01);
		
	}

	
	gameCamera->frustumCamera.pos = gameObjectX->transform->position;
	

}
