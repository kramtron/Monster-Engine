#include "Globals.h"
#include "Application.h"
#include "ModuleResources.h"

ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//Init physfs
	PHYSFS_init(nullptr);
	PHYSFS_mount(".", nullptr, 1);
	PHYSFS_setWriteDir("Assets");

}

ModuleResources::~ModuleResources()
{



}



update_status ModuleResources::Update(float dt)
{


	

	ImMainMenuBar::ThemeStyleW();
	ImMainMenuBar::ThemeStyleChanger();

	ImGui::Begin("Assets", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	PrintFolders((char*)pathName.c_str());

	ImGui::End();

	ImGui::PopStyleColor(6);

	return UPDATE_CONTINUE;
}

update_status ModuleResources::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

bool ModuleResources::CleanUp()
{
	bool ret = true;


	//Delete physfs
	PHYSFS_deinit();

	return ret;
}



void ModuleResources::PrintFolders(char* path)
{
	char** path1 = PHYSFS_enumerateFiles(path);
	char** path2;



}
