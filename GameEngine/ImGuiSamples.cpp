#include "ImGuiSamples.h"
#include "ImConfigWindow.h"


Application* ImGuiSamples::App = nullptr;
ImGuiIO* ImGuiSamples::id = nullptr;

ImHierarchyWindow* ImGuiSamples::ImH = nullptr;


ImInspectorWindow* ImGuiSamples::ImI = nullptr;

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

	ImH = new ImHierarchyWindow();
	ImI = new ImInspectorWindow();

	//Primitive::ImH = ImH;
}

void ImGuiSamples::NewFrame(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());


	

	if(ImH->gameObjectSelected !=nullptr)
	App->camera->gOpos = ImH->gameObjectSelected->transform;
	



	//Pasar esto a una lista??
	ImMainMenuBar::Update(App,ImH);
	ImHierarchyWindow::Update(ImH);
	ImSceneWindow::Update(App);
	Console::PrintDebug();
	ImInspectorWindow::Update(ImH,ImI);
	ImConfigWindow::Update(App, dt);
	ImGameWindow::Update(App);



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
