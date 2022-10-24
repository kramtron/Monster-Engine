#include "S_GameObject.h"

GameObject::GameObject(const char* name, GameObject* parent)
{
	if (parent != nullptr) {
		parent->children.push_back(this);
	}

}

GameObject::~GameObject()
{
	//Shouldn't be memory leaks here
	for (uint i = 0; i < children.size(); i++) {
		delete children[i];
		children[i] = nullptr;
	}
	children.clear();


	for (uint i = 0; i < components.size(); i++) {
		delete components[i];
		components[i] = nullptr;
	}
	components.clear();
}

Component* GameObject::AddComponent(Component::Type type)
{
	switch (type)
	{
	case Component::Type::Transform:
		break;
	case Component::Type::Material:
		break;
	case Component::Type::Mesh:
		break;
	case Component::Type::Light:
		break;
	}

	return nullptr;
}

Component* GameObject::GetComponent(Component::Type type)
{

	for (uint i = 0; i < components.size(); i++)
	{
		if (components[i]->type == type)
			return components[i];
	}
	return nullptr;
}

void GameObject::Enable()
{
	active = true;
}

void GameObject::Disable()
{
	active = false;
}

bool GameObject::IsActive()
{
	return active;
}

bool GameObject::IsSelected()
{
	return selected;
}
