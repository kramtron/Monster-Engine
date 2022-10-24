#include "ImHierarchyWindow.h"



ImHierarchyWindow::ImHierarchyWindow()
{
}

ImHierarchyWindow::~ImHierarchyWindow()
{
}

void ImHierarchyWindow::Update()
{
	ImHierarchyWindow* ImH = new ImHierarchyWindow;

	if (ImGui::Begin("Hierarchy")) {

		//DrawGameObject();
		if ((ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Right && ImGui::IsWindowHovered()) || ImH->popedUp)) {
			ImH->popedUp = true;

		}


	}

	ImGui::End();
}

uint ImHierarchyWindow::DrawGameObject(GameObject* gO)
{
	return uint();
}

uint ImHierarchyWindow::AddGameObject(GameObject* gO)
{
	//Add in GameObject Tree
	gameObjects[IDCounter] = gO;

	return IDCounter++;
}

void ImHierarchyWindow::StartGameObject(GameObject* gO, int iterations)
{
	ImGuiTreeNodeFlags nodeFlags = baseFlags;

	bool openNode;

	if (gO == gameObjectSelected)nodeFlags |= ImGuiTreeNodeFlags_Selected;

	if (gO->children.empty()) {
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx((void*)(intptr_t)iterations, nodeFlags, gO->name.c_str(),iterations);
		openNode = false;
	}
	else {
		openNode = ImGui::TreeNodeEx((void*)(intptr_t)iterations, nodeFlags, gO->name.c_str(), iterations);
	}

	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("GameObject", gO, sizeof(GameObject*));
		
		gameObjectDragging = gO;
		ImGui::Text("Change parent of GameObject");
		ImGui::EndDragDropSource();
	}
	if (ImGui::IsItemHovered()) {
		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Left))SetGameObjectSelected(gO);
		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Right))gameObjectRightClick = gO;
	}


}

void ImHierarchyWindow::SetGameObjectSelected(GameObject* gO)
{
	gameObjectSelected = gO;

}
