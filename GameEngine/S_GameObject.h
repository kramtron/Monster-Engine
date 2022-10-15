#pragma once

#include "Globals.h"
#include "Application.h"

#include<vector>
#include<string>

#include "S_Component.h"

using namespace std;

class GameObject
{

public:

	GameObject();
	~GameObject();


	Component* AddComponent(Component::Type type);
	Component* GetComponent(Component::Type type);

	void Enable();
	void Disable();

public:
	
	vector<GameObject*> children;
	vector<Component*> components;

	std::string name;

	bool active = false;



};

