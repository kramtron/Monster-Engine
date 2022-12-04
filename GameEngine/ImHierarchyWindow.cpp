#include "ImHierarchyWindow.h"
#include "ImMainMenuBar.h"

Application* ImHierarchyWindow::App = nullptr;




ImHierarchyWindow::ImHierarchyWindow()
{
	rootGameObject = new GameObject("Scene", nullptr,"none");

	




	GameObject* gO4 = new GameObject("Street", rootGameObject, "first");
	MeshLoader::LoadFile("Assets/street/scene.DAE", gO4);
	gO4->transform->rotation = float3(0.0f,0.0f,0.0f);
	gO4->transform->TransformToUpdate();
	
	GameObject* gO5 = new GameObject("Main Camera", rootGameObject, "first");
	gO5->AddComponent(Component::Type::Camera);

	GameObject* gO = new GameObject("BakerHouse", rootGameObject, "first");
	MeshLoader::LoadFile("Assets/BakerHouse.fbx", gO);
	/*gO->children[0]->transform->ResetTransform();
	gO->children[1]->transform->ResetTransform();*/

	//gO->meshR = (C_Mesh*)gO->AddComponent(Component::Type::Mesh);
	//gO->children[0]->transform->ResetTransform();
	/*GameObject* gO2 = new GameObject("Sphere", rootGameObject, "first");
	gO2->meshes = MeshLoader::LoadFile("Assets/Sphere.fbx", gO2);
	gO2->meshR = (C_Mesh*)gO2->AddComponent(Component::Type::Mesh);


	GameObject* gO3 = new GameObject("Cube", rootGameObject, "first");
	gO3->meshes = MeshLoader::LoadFile("Assets/Cube.fbx", gO3);
	gO3->meshR = (C_Mesh*)gO3->AddComponent(Component::Type::Mesh);*/
	//gO3->transform->position.x = 4;
	referenceGameObject = &App->dummy->gameObjects;

	//referenceGameObject = &App->dummy->gameObjects;

	baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	isEnable = true;

}

ImHierarchyWindow::~ImHierarchyWindow()
{
}

void ImHierarchyWindow::Update(ImHierarchyWindow* ImH)
{


	//ImH->referenceGameObject = &App->dummy->gameObjects;
	App->camera->selectedGameObejct = ImH->GetGameObjectSeldcted();
	
	ImMainMenuBar::ThemeStyleChanger();
	ImMainMenuBar::ThemeStyleW();
	
	if (ImGui::Begin("Hierarchy")) {

		//for (int i = 1; i < ImH->referenceGameObject->size(); i++) {
			//ImH->DrawGameObjectsChilds(ImH->referenceGameObject->at(i));
			ImH->DrawGameObjectsChilds(ImH->rootGameObject);
		//}
		
	}

	ImGui::PopStyleColor(6);

	ImGui::End();
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

		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Left))
			SetGameObjectSelected(gO);

		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Right))
			gameObjectRightClick = gO;

	}
	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* imGuiPayLoad = ImGui::AcceptDragDropPayload("GameObject")) {
			gameObjectDragging->SetParent(gO);
			gameObjectDragging->parent->RemoveChild(gO);
			gameObjectDragging = nullptr;
		}
		ImGui::EndDragDropTarget();
	}
	if (openNode) {
		if (!gO->children.empty())
			DrawGameObjectsChilds(gO, true);
		ImGui::TreePop();
	}


}

void ImHierarchyWindow::SetGameObjectSelected(GameObject* gO)
{
	gameObjectSelected = gO;

}

void ImHierarchyWindow::DrawGameObjectsChilds(GameObject* gO, bool childOnly)
{
	if (!childOnly) StartGameObject(gO, 0);
	else {
		for (int i = 0; i < gO->children.size(); i++) {
			StartGameObject(gO->children[i], i);
		}
	}
}
