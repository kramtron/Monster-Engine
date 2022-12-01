#pragma once
#include "Globals.h"
#include "Application.h"



struct FileInfo {

public:
	FileInfo(string path);


public:

	string path, name, extension;
	bool folder;

};
