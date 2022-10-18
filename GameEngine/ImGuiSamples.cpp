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
	id->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Platform/Renderer backends
	//ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	
	

}

void ImGuiSamples::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;


	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);


	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("InvisibleWindow", nullptr, windowFlags);


	

	ImGui::PopStyleVar(3);

	ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindow");

	ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

	ImGui::End();


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
	Console::PrintDebug();

}

void ImGuiSamples::Render()
{
	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)id->DisplaySize.x, (int)id->DisplaySize.y);


	//Always last
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
	if (id->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

void ImGuiSamples::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

}
