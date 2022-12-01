#include "Globals.h"
#include "Application.h"
#include "ModuleResources.h"

ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//Init physfs
	PHYSFS_init(nullptr);
	PHYSFS_mount(".", nullptr, 1);
	SetNewPath("Assets");

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

	Refresh();

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
	//AddFolders(path, assets);

	PHYSFS_freeList(assets);
}


void ModuleResources::PrintFolders()
{

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::Button("New Folder")) {
			CreateFolder(NEW_FOLDER_PATH);
			refresh = true;
		}



		ImGui::EndMenuBar();
	}


	for (int i = 0; i < assetsList.size(); i++) {
		FileInfo tempFile = assetsList[i];

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

		
		bool TreeNodeEx = ImGui::TreeNodeEx((void*)(intptr_t)&tempFile, treeNodeFlags, tempFile.name.c_str());

		if (ImGui::IsItemHovered())
		{
			
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
			{
				DeleteFolder(tempFile);
			}
			
			else if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
			{
				if (tempFile.folder)
					SetNewPath(tempFile.path.c_str());
			}
			

		}

		if (TreeNodeEx)
		{
			ImGui::TreePop();
		}
	
		ImGui::Separator();
	}

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

void ModuleResources::DeleteFolder(FileInfo path)
{
	PHYSFS_delete(path.name.c_str());
	refresh = true;

}


