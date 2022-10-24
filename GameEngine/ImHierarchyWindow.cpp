#include "ImHierarchyWindow.h"



ImHierarchyWindow::ImHierarchyWindow()
{
}

ImHierarchyWindow::~ImHierarchyWindow()
{
}

void ImHierarchyWindow::Update()
{

	if (ImGui::Begin("Hierarchy")) {

		//DrawGameObject();
		if ((ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Right && ImGui::IsWindowHovered()) || popedUp)) {
			popedUp = true;

		}


	}

	ImGui::End();
}

uint ImHierarchyWindow::AddGameObject(GameObject* gO)
{
	gameObjects[IDCounter] = gO;

	return IDCounter++;
}
