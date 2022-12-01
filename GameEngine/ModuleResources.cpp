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

	PrintFolders();

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


void ModuleResources::PathInfo(const char* path)
{
	char** assets = PHYSFS_enumerateFiles(path);

	ClearAssetsList();

	AddFolders(path, assets);
	AddFolders(path, assets);

	PHYSFS_freeList(assets);
}


void ModuleResources::PrintFolders()
{
	

}



void ModuleResources::AddFolders(const char* path, char** assets)
{

	for (int i = 0; assets[i] != NULL; i++) {
		string tempPath = path;
		tempPath.append("/").append(assets[i]);
		FileInfo tempFileInfo(tempPath);
		if (!tempFileInfo.folder) {
			assetsList.push_back(tempFileInfo);
		}
	}
}


