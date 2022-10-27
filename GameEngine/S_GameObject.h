#pragma once

#include "Globals.h"
#include "Application.h"
#include "R_Mesh.h"

#include<vector>
#include<string>

#include "S_Component.h"
#include "C_Transform.h"

using namespace std;

class M_Mesh;

class GameObject
{

public:

	GameObject(std::string name, GameObject* parent, string tag, M_Mesh* our_mesh);
	~GameObject();


	Component* AddComponent(Component::Type type);
	Component* GetComponent(Component::Type type);

	std::vector<Component*>GetComponents() { return components; }

	void Enable();
	void Disable();

	bool IsActive();

	bool IsSelected();

	bool SetParent(GameObject* p);

	bool AddChild(GameObject* c);

	void RemoveChild(GameObject* c);




public:
	
	vector<GameObject*> children;
	vector<Component*> components;

	std::string name;
	std::string tag;

	bool active = true;

	bool selected = false;
	GameObject* parent = nullptr;

	static Application* App;

	M_Mesh* mesh;

	C_Transform* transform = nullptr;

};

