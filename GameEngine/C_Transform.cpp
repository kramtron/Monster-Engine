#include "C_Transform.h"
#include "S_GameObject.h"

C_Transform::C_Transform(GameObject* gO) : Component(gO)
{
	gameObject = gO;

	/*globalTransform.SetIdentity();
	localTransform.SetIdentity();
	localTransform.Decompose(position, rotation, scale);
	eRotation = rotation.ToEulerXYZ();
	globalTransformT = globalTransform.Transposed();*/

	ResetTransform();

}

C_Transform::~C_Transform()
{
}


void C_Transform::TransformToUpdate()
{

	//Forma final no va aun
	/*std::vector<C_Transform*> tToUpdate;
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

	tToUpdate.clear();*/



	float rx = rotation.x * DEGTORAD;
	float ry = rotation.y * DEGTORAD;
	float rz = rotation.z * DEGTORAD;

	//Rotation
	matrix[0] = cos(rz) * cos(ry) * scale.x;
	matrix[1] = -sin(rz) * cos(rx) + cos(rz) * sin(ry) * sin(rx);
	matrix[2] = sin(rz) * sin(rx) + cos(rz) * sin(ry) * cos(rx);

	matrix[4] = sin(rz) * cos(ry);
	matrix[5] = (cos(rz) * cos(rx) + sin(rz) * sin(ry) * sin(rx)) * scale.y;
	matrix[6] = -cos(rz) * sin(rx) + sin(rz) * sin(ry) * cos(rx);

	matrix[8] = -sin(ry);
	matrix[9] = cos(ry) * sin(rx);
	matrix[10] = cos(ry) * cos(rx) * scale.z;

	//position
	matrix[3] = position.x;
	matrix[7] = position.y;
	matrix[11] = position.z;

	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;


}




void C_Transform::InspectorW() {

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

		int offSet = ImGui::CalcTextSize("Position: ").x + 16;
		ImGui::Text("Position: ");
		ImGui::SameLine();
		if (ImGui::DragFloat3("Pos", &position, 0.1f)) {
			TransformToUpdate();
		}

		ImGui::Text("Rotation: ");
		ImGui::SameLine();
		if (ImGui::DragFloat3("Rot", &rotation, 0.1f)) {
			TransformToUpdate();

		}

		ImGui::Text("Scale:    ");
		ImGui::SameLine();
		if (ImGui::DragFloat3("Scale", &scale, 0.1f)) {
			TransformToUpdate();

		}

		if (ImGui::Button("Reset Transform"))
			ResetTransform();
	}

}



void C_Transform::ResetTransform()
{

	position = rotation = { 0, 0, 0 };
	scale = { 1, 1, 1 };
	matrix = { 1, 0, 0, 0,
			   0, 1, 0, 0,
			   0, 0, 1, 0,
			   0, 0, 0, 1 };

	TransformToUpdate();

}

/*C_Transform* C_Transform::GetDescendingTransforms(C_Transform* node, std::vector<C_Transform*>& transform)
{

	/*transform.push_back(node);

	if (!node->gameObject->children.empty()) {
		for (size_t i = 0; i < node->gameObject->children.size(); i++) {
			C_Transform* pTransform = node->gameObject->children[i]->transform;
				GetDescendingTransforms(pTransform, transform);
			
		}
	}


	return nullptr;
}*/
