#include "ImInspectorWindow.h"

bool ImInspectorWindow::isEnable = true;

ImInspectorWindow::ImInspectorWindow()
{
}

ImInspectorWindow::~ImInspectorWindow()
{
}

void ImInspectorWindow::Update()
{

	if (ImGui::Begin("Inspector"), isEnable) {



	}

	ImGui::End();


}
