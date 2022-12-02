#pragma once
#include "Module.h"
#include "Globals.h"
#include "ImMainMenuBar.h"
#include "physfs.h"
#include "T_FileInfo.h"
#define NEW_FOLDER_PATH "Folder/"
#define PATH_NAME "Assets"
#pragma comment( lib, "External_Libraries/PhysFS/libx86/physfs.lib" )

typedef unsigned int uint;

#include <vector>

struct File;


class ModuleResources : public Module
{
public:

	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();



	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();

public:


	uint Find(const char* path) const;
	uint ImportFile(const char* path);


	
	void PrintFolders();

	void PathInfo(const char* path);


	void AddFolders(const char* path, char** assets);
	void AddFiles(const char* path, char** assets);

	void DeleteFolder(File path);

	void GoBackPath();
	
public:

	void CreateFolder(char* path) {
		
		PHYSFS_mkdir(path);
		refresh = true;

	}


	void SetNewPath(const char* path) {
		newPath = path;
		PHYSFS_setWriteDir(path);
		PathInfo(path);
	}

	void ClearAssetsList() {
		assetsList.clear();
	}

	void Refresh() {
		if (refresh) {
			PathInfo(newPath.c_str());
			refresh = false;
		}
	}
private:

	vector<File> assetsList;

	string newPath;
	//const ModuleResources* RequestResource(uint uid) const;
	bool refresh = false;
	int folderCounter = 0;

};

