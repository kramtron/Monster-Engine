#include "C_Transform.h"

C_Transform::C_Transform(GameObject* gO) : Component(gO)
{

}

C_Transform::~C_Transform()
{
}

void C_Transform::InspectorW() {

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {


	}

}
