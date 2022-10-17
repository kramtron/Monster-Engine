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

	GameObject(const char* name, GameObject* parent);
	~GameObject();


	Component* AddComponent(Component::Type type);
	Component* GetComponent(Component::Type type);

	void Enable();
	void Disable();

	bool isActive();

public:
	
	vector<GameObject*> children;
	vector<Component*> components;

	std::string name;

	bool active = false;



};

