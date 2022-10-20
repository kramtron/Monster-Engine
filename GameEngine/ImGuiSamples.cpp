#include "ImGuiSamples.h"

Application* ImGuiSamples::App = nullptr;
ImGuiIO* ImGuiSamples::id = nullptr;

static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

void ImGuiSamples::Init()
{

	//
	//ImGui
	//
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();


	id = &ImGui::GetIO(); (void)id; 


	id->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	id->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//id->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Platform/Renderer backends
	//ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	ImGuiStyle& style = ImGui::GetStyle();

	if (id->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 10.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.0f;
		style.Colors[ImGuiCol_Border] = ImVec4(255, 1, 1, 255);


	}
	
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

	//WRONG¿?
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImGuiSamples::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());


	if (ImGui::BeginMainMenuBar()){

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.05f, 0.05f, 0.05f, 1));

		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.95f, 0.95f, 0.95f, 1));

		if (ImGui::BeginMenu("Application"))
		{
			if (ImGui::MenuItem("Close Appplication"))
			{
				// TODO: Exit application
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			/*for (int i = 0; i < (uint)ImWindowID::MAX; i++)
			{
				if (ImGui::MenuItem(imWindows[i]->windowName.c_str())) imWindows[i]->isEnabled = true;
			}*/
			ImGui::EndMenu();
		}

		ImGui::PopStyleColor(2);

		ImGui::EndMainMenuBar();

	}


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

	}


	ImGui::EndMenuBar();
	ImGui::BeginChild("", ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));

	ImVec2 wsize = ImGui::GetWindowSize();

	ImGui::Image((ImTextureID)App->renderer3D->textureColorbuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::EndChild();
	ImGui::End();



	//Pasar esto a una lista??
	Console::PrintDebug();
	ImInspectorWindow::Update();
	ImHierarchyWindow::Update();



	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

}

void ImGuiSamples::Render()
{
	
}

void ImGuiSamples::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

}
