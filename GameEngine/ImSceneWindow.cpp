#include "ImSceneWindow.h"




ImSceneWindow::ImSceneWindow()
{
}

ImSceneWindow::~ImSceneWindow()
{
}

void ImSceneWindow::Update(Application* App)
{

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


	ImGui::EndMenuBar();
	ImGui::BeginChild("", ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));

	ImVec2 wsize = ImGui::GetWindowSize();
	//ImVec2 wsize = ImGui::GetContentRegionAvail();

	/*ImVec2 newSize = wsize;

	newSize.x = (newSize.y / 9.0f) * 16.0f;

	float ofset = (wsize.x - newSize.x) / 2.0f;

	ofset /= newSize.x;*/


	ImGui::Image((ImTextureID)App->renderer3D->textureColorbuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::EndChild();
	ImGui::End();
}
