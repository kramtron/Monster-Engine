#include "ImMainMenuBar.h"



bool ImMainMenuBar::styleSelectD = false;
bool ImMainMenuBar::styleSelectL = false;
bool ImMainMenuBar::styleSelectSD = true;
bool ImMainMenuBar::styleSelectP = false;


int ImMainMenuBar::colorStyle = 3;

float ImMainMenuBar::colorWind[4] = { 0.4f, 0.7f, 0.0f, 1.0f };
float ImMainMenuBar::colorText[4] = { 0.4f, 0.7f, 0.0f, 1.0f };


ImMainMenuBar::~ImMainMenuBar()
{
}

void ImMainMenuBar::Update(Application* App, ImHierarchyWindow* imH)
{
	GameObject* root = imH->rootGameObject;

	ThemeStyleChanger();

	if (ImGui::BeginMainMenuBar()) {

		/*ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.05f, 1.05f, 1.05f, 1));

		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.0f, 0.0f, 0.0f, 1));*/

		if (ImGui::BeginMenu(" File "))
		{
			

			if (ImGui::MenuItem(" GitHub ")) {

				ShellExecute(0, 0, "https://github.com/kramtron/Monster-Engine", 0, 0, SW_SHOW);

			}
			if (ImGui::MenuItem(" Exit ")) {


			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(" GameObjects "))
		{

			if (ImGui::MenuItem(" Emty GameObject  "))
			{

				Primitive p;
				p.CreatePrimitive(root, PrimitiveType::EMPTY);

			}

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

		if (ImGui::BeginMenu("Windows")) {
			
			if (ImGui::BeginMenu("Theme")) {
				if (ImGui::MenuItem(" Light ", NULL, &styleSelectL)) {

					colorStyle = 1;
					styleSelectL = true;
					styleSelectD = false;
					styleSelectSD = false;
					styleSelectP = false;

				}


				if (ImGui::MenuItem(" MidNight  ", NULL, &styleSelectSD))
				{
					colorStyle = 3;
					styleSelectL = false;
					styleSelectD = false;
					styleSelectSD = true;
					styleSelectP = false;
				}

				if (ImGui::MenuItem(" Dark  ", NULL, &styleSelectD))
				{
					colorStyle = 2;
					styleSelectL = false;
					styleSelectD = true;
					styleSelectSD = false;
					styleSelectP = false;
				}
				ImGui::EndMenu();

			}
			ImGui::EndMenu();

		}

		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);

		ImGui::EndMainMenuBar();

	}
}

void ImMainMenuBar::ThemeStyleChanger()
{
	if (colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));


		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));


	}
	else if (colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));

		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.0f, 0.0f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.0f, 0.0f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	
}




void ImMainMenuBar::ThemeStyleW()
{
	if (colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.9, 0.9, 0.9, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
}
