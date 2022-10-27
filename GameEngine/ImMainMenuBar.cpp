#include "ImMainMenuBar.h"



ImMainMenuBar::~ImMainMenuBar()
{
}

void ImMainMenuBar::Update(Application* App, ImHierarchyWindow* imH)
{
	GameObject* root = imH->rootGameObject;
	if (ImGui::BeginMainMenuBar()) {

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.05f, 1.05f, 1.05f, 1));

		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.0f, 0.0f, 0.0f, 1));

		if (ImGui::BeginMenu(" File "))
		{
			/*if (ImGui::MenuItem("  Git Hub  "))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("GitHub", ImVec2(60, 20)))
				ShellExecute(0, 0, "https://github.com/kramtron/Monster-Engine", 0, 0, SW_SHOW);

			if (ImGui::MenuItem("  Exit  "))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("Exit", ImVec2(60, 20)))
				//quit = true;*/

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(" GameObjects "))
		{
			if (ImGui::MenuItem(" Plane  "))
			{
				
				Primitive p;
				p.CreatePrimitive(root,PrimitiveType::PLANE);

			}

			if (ImGui::MenuItem(" Cube  "))
			{

				Primitive p;
				p.CreatePrimitive(root, PrimitiveType::CUBE);

			}

			if (ImGui::MenuItem(" Sphere  "))
			{

				Primitive p;
				p.CreatePrimitive(root, PrimitiveType::SPHERE);

			}

			if (ImGui::MenuItem(" Cylinder  "))
			{

				Primitive p;
				p.CreatePrimitive(root, PrimitiveType::CYLINDER);

			}

			ImGui::EndMenu();
		}

		ImGui::PopStyleColor(2);

		ImGui::EndMainMenuBar();

	}
}
