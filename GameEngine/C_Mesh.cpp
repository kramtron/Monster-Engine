#include "C_Mesh.h"
#include "S_GameObject.h"

C_Mesh::C_Mesh(GameObject* gO) : Component(gO)
{

	gameObject = gO;


}

C_Mesh::~C_Mesh()
{
}

void C_Mesh::InspectorW()
{


	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::Checkbox("Render Mesh", &gameObject->renderMesh);
		ImGui::Checkbox("Render AABB boxes", &gameObject->renderAABB);

		ImGui::TextWrapped("Mesh vertices: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(gameObject->mesh->num_vertices).c_str());

		ImGui::TextWrapped("Mesh indices: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(gameObject->mesh->num_indices).c_str());


	}
}
