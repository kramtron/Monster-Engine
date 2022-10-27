#include "C_Transform.h"

C_Transform::C_Transform(GameObject* gO) : Component(gO)
{

}

C_Transform::~C_Transform()
{
}

void C_Transform::InspectorW() {

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

		int offSet = ImGui::CalcTextSize("Position: ").x + 16;
		ImGui::Text("Position: ");
		ImGui::SameLine();
		if (ImGui::DragFloat3("Pos", &position[0], 0.1f)) {

		}


	}

}
