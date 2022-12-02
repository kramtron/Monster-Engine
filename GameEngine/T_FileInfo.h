#pragma once
#include "Globals.h"
#include "Application.h"



struct File {

public:
	File(string path);


public:

	string path, name, extension;
	bool folder;
	bool selected = false;

};
