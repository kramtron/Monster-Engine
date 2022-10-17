#pragma once

#include <string>


using namespace std;
class ImMainWindow
{
public:

	ImMainWindow() {};

	virtual ~ImMainWindow() {};

	virtual bool Update() = 0;

	bool isEnable = true;

	string windowName = "DefaultWindow";


};

