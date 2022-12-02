#include "T_FileInfo.h"

File::File(string path)
{
	//Copy the path
	this->path = path;

	//Copy the name
	this->name= path.substr(path.find_last_of("/") + 1);
	this->folder = (path.find(".") == -1);

	if (!folder) this->extension = path.substr(path.find_last_of("."));
	else this->extension = "";
}
