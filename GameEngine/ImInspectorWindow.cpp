#include "ImInspectorWindow.h"
#include "ImMainMenuBar.h"



bool ImInspectorWindow::isEnable = true;

ImInspectorWindow::ImInspectorWindow()
{
	isEnable = true;
}

ImInspectorWindow::~ImInspectorWindow()
{
}

void ImInspectorWindow::Update(ImHierarchyWindow* ImH, ImInspectorWindow* ImI)
{

	ImI->gameObjectSelected = ImH->GetGameObjectSeldcted();

	ImMainMenuBar::ThemeStyleChanger();
	ImMainMenuBar::ThemeStyleW();

	if (ImGui::Begin("Inspector"), &isEnable) {

		if (ImI->gameObjectSelected) {
			ImGui::InputText("Name", (char*)&ImI->gameObjectSelected->name, 0);

			std::vector<Component*> components = ImI->gameObjectSelected->GetComponents();

			for (auto* component : components) {
				component->InspectorW();
			}
		}

	}

	ImGui::End();

	ImGui::PopStyleColor(6);

}


