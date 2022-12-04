#include "ImSceneWindow.h"
#include "ImMainMenuBar.h"
#include "R_Mesh.h"



ImSceneWindow::ImSceneWindow()
{
}

ImSceneWindow::~ImSceneWindow()
{
}

void ImSceneWindow::Update(Application* App, ImHierarchyWindow* ImH)
{
	ImMainMenuBar::ThemeStyleChanger();
	ImMainMenuBar::ThemeStyleW();

	ImSceneWindow tempSc;

	ImGui::Begin("SceneTest", 0, ImGuiWindowFlags_MenuBar);


	ImGui::BeginMenuBar();
	//ImGui::SameLine(0, -50);

	if (ImGui::Button("Play")) {
		//Play mode
	}
	//ImGui::SameLine(ImGui::GetWindowWidth() - 95.0f);
	ImGui::Separator();

	if (ImGui::Button("WireFrame")) {
		//wireFrame = !wireFrame;
		App->dummy->wireFrame = !App->dummy->wireFrame;

	}
	/*if (ImGui::Button("Center Camera to GO")) {
		//wireFrame = !wireFrame;
		App->camera->center = !App->camera->center;

	}*/

	ImGui::EndMenuBar();
	//ImGui::BeginChild("", ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));

	//ImVec2 wsize = ImGui::GetWindowSize();
	ImVec2 wsize = ImGui::GetContentRegionAvail();

	ImVec2 newSize = wsize;

	newSize.x = (newSize.y / 9.0f) * 16.0f;

	float ofset = (wsize.x - newSize.x) / 2.0f;

	ofset /= newSize.x;


	ImGui::Image((ImTextureID)App->camera->sceneCamera->cameraBuffer.GetTextureBuffer(), wsize, ImVec2(-ofset, 1), ImVec2(1 + ofset, 0));


	if (ImGui::IsMouseClicked(0) && App->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT && ImGui::IsWindowHovered())
	{

		std::vector<GameObject*> gOTouched;


		ImVec2 mousePos = ImGui::GetMousePos();
		ImVec2 norm = tempSc.GetMousePosNormalized(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + ImGui::GetFrameHeight(), ImGui::GetWindowSize().x, ImGui::GetWindowSize().y - ImGui::GetFrameHeight(), mousePos);
		LineSegment picking = App->camera->sceneCamera->frustumCamera.UnProjectLineSegment(norm.x, norm.y);


		//vector meshes vinculado correctamente
		for (size_t i = 0; i < App->renderer3D->rMeshes.size(); i++) {


			if (picking.Intersects(App->renderer3D->rMeshes[i]->OBB_))
			{
				if (App->renderer3D->rMeshes[i]->myGO != nullptr) {

					gOTouched.push_back(App->renderer3D->rMeshes[i]->myGO);

				}
			}
		}

		float distance;
		float minDist = 0;

		for (size_t i = 0; i < gOTouched.size(); i++) {



			M_Mesh* tempMesh = gOTouched[i]->mesh;

			float4x4 tempMat = gOTouched[i]->transform->GetGlobalT();


			if (tempMesh->num_indices > 6) {

				if (tempMesh != nullptr) {
					//Need j+=3 if no this no work
					for (int j = 0; j < tempMesh->num_indices; j+=3) {

						

							float* tempF1 = &tempMesh->vertices[tempMesh->indices[j] * VERTEX_ARGUMENTS];
							float* tempF2 = &tempMesh->vertices[tempMesh->indices[j + 1] * VERTEX_ARGUMENTS];
							float* tempF3 = &tempMesh->vertices[tempMesh->indices[j + 2] * VERTEX_ARGUMENTS];
							float4 tempF4 = tempMat * float4(*tempF1, *(tempF1 + 1), *(tempF1 + 2), 1);
							float4 tempF5 = tempMat * float4(*tempF2, *(tempF2 + 1), *(tempF2 + 2), 1);
							float4 tempF6 = tempMat * float4(*tempF3, *(tempF3 + 1), *(tempF3 + 2), 1);
							float3 tempF7 = float3(tempF4.x, tempF4.y, tempF4.z);
							float3 tempF8 = float3(tempF5.x, tempF5.y, tempF5.z);
							float3 tempF9 = float3(tempF6.x, tempF6.y, tempF6.z);

						Triangle tempTriangle(tempF7, tempF8, tempF9);

						if (picking.Intersects(tempTriangle, &distance, nullptr))
						{

							if (minDist == 0) {
								minDist = distance;
								ImH->SetGameObjectSelected(gOTouched[i]);
								continue;
							}

							if (minDist > distance) {
								minDist = distance;
								ImH->SetGameObjectSelected(gOTouched[i]);


							}
						}


					}
				}
			}

		}

		if (gOTouched.size() == 0) App->camera->selectedGameObejct = nullptr;

		gOTouched.clear();


	}

	//ImGui::EndChild();
	ImGui::End();

	ImGui::PopStyleColor(6);

}

ImVec2 ImSceneWindow::GetMousePosNormalized(float x, float y, float w, float h, ImVec2 p)
{

	return ImVec2(0,0);
}
