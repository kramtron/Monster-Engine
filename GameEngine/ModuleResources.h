#pragma once
#include "Module.h"
#include "Globals.h"
#include "ImMainMenuBar.h"
#include "physfs.h"

#define NEW_FOLDER_PATH "Default_New_Folder/"

#pragma comment( lib, "External_Libraries/PhysFS/libx86/physfs.lib" )

typedef unsigned int uint;


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


	
	void PrintFolders(char* path);

public:

	void CreateFolder(char* path) {
		PHYSFS_mkdir(path);
	}


	void DeleteFolder(char* path) {
		PHYSFS_delete(path);

	}

private:
	string pathName = "Assets";

	//const ModuleResources* RequestResource(uint uid) const;


};

