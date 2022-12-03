#include "ImGameWindow.h"
#include "ImMainMenuBar.h"


ImGameWindow::ImGameWindow()
{
}

ImGameWindow::~ImGameWindow()
{
}

void ImGameWindow::Update(Application* App)
{

	ImMainMenuBar::ThemeStyleChanger();
	ImMainMenuBar::ThemeStyleW();


	ImGui::Begin("Game", 0, ImGuiWindowFlags_MenuBar);

	ImVec2 wsize = ImGui::GetContentRegionAvail();

	ImVec2 newSize = wsize;

	newSize.x = (newSize.y / 9.0f) * 16.0f;

	float ofset = (wsize.x - newSize.x) / 2.0f;

	ofset /= newSize.x;


	ImGui::Image((ImTextureID)App->camera->gameCamera->cameraBuffer.GetTextureBuffer(), wsize, ImVec2(-ofset, 1), ImVec2(1 + ofset, 0));


	ImGui::End();


	ImGui::PopStyleColor(6);

}
