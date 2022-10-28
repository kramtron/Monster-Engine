#include "C_Transform.h"
#include "S_GameObject.h"

C_Transform::C_Transform(GameObject* gO) : Component(gO)
{
	gameObject = gO;

	globalTransform.SetIdentity();
	localTransform.SetIdentity();
	localTransform.Decompose(position, rotation, scale);
	eRotation = rotation.ToEulerXYZ();
	globalTransformT = globalTransform.Transposed();

}

C_Transform::~C_Transform()
{
}


void C_Transform::TransformToUpdate()
{
	std::vector<C_Transform*> tToUpdate;
	GetDescendingTransforms(this, tToUpdate);

	rotation = Quat::FromEulerXYX(eRotation.x * DEGTORAD, eRotation.y * DEGTORAD, eRotation.z * DEGTORAD);

	localTransform = float4x4::FromTRS(position, rotation, scale);

	if (!tToUpdate.empty()) {
		for (size_t i = 0; i < tToUpdate.size(); i++) {
			if (tToUpdate[i]->gameObject->parent != nullptr) {
				C_Transform* pTransform = tToUpdate[i]->gameObject->parent->transform;

				if (pTransform != nullptr) {
					tToUpdate[i]->globalTransform = pTransform->globalTransform * tToUpdate[i]->localTransform;
					tToUpdate[i]->globalTransformT = tToUpdate[i]->globalTransform.Transposed();


				}
			}
		}
	}

	tToUpdate.clear();

}




void C_Transform::InspectorW() {

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

		int offSet = ImGui::CalcTextSize("Position: ").x + 16;
		ImGui::Text("Position: ");
		ImGui::SameLine();
		if (ImGui::DragFloat3("Pos", &position[0], 0.1f)) {
			TransformToUpdate();
		}

		ImGui::Text("Rotation: ");
		ImGui::SameLine();
		if (ImGui::DragFloat3("Rot", &eRotation[0], 0.1f)) {
			TransformToUpdate();

		}

		ImGui::Text("Scale:    ");
		ImGui::SameLine();
		if (ImGui::DragFloat3("Scale", &scale[0], 0.1f)) {
			TransformToUpdate();

		}

		if (ImGui::Button("Reset Transform"))
			ResetTransform();
	}

}

void C_Transform::ResetTransform()
{
	position = eRotation = float3::zero;
	scale = float3::one;
	TransformToUpdate();

}

C_Transform* C_Transform::GetDescendingTransforms(C_Transform* node, std::vector<C_Transform*>& transform)
{

	transform.push_back(node);

	if (!node->gameObject->children.empty()) {
		for (size_t i = 0; i < node->gameObject->children.size(); i++) {
			C_Transform* pTransform = node->gameObject->children[i]->transform;
				GetDescendingTransforms(pTransform, transform);
			
		}
	}


	return nullptr;
}
