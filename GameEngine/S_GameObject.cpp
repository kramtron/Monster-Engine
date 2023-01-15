#include "S_GameObject.h"
#include "ImHierarchyWindow.h"
#include "T_TextureLoader.h"
#include "C_Camera.h"
#include "C_Animation.h"
Application* GameObject::App = nullptr;


GameObject::GameObject(std::string name = "default", GameObject* parent = nullptr, std::string tag = "default" ) : name(name), tag(tag)
{

	App->dummy->AddGameObject(this);
	transform = (C_Transform*)AddComponent(Component::Type::Transform);

	

	
	if (parent != nullptr) {
		parent->children.push_back(this);
		this->parent = parent;
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
	LOG("Can't create a NONE component", ConsoleType::SYSTEM);
	Component* comp = nullptr;
	switch (type)
	{
	case Component::Type::Transform:
		if (transform == nullptr) {
			comp = new C_Transform(this);
		}
		break;
	case Component::Type::Material:
		break;
	case Component::Type::Mesh:
		comp = new C_Mesh(this);
		break;
	case Component::Type::Light:
		break;
	case Component::Type::Camera:
		comp = new C_Camera(this,App);
		break;
	case Component::Type::Animation:
		comp = new C_Animation(this);
		break;
	}

	if (comp != nullptr) {
		comp->type = type;
		components.push_back(comp);
	}
	return comp;

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

bool GameObject::SetParent(GameObject* p)
{
	return p->AddChild(this);
}

bool GameObject::AddChild(GameObject* c)
{
	if (!c)
		return false;

	if (c->parent == this) 
		return false;

	GameObject* p = parent;

	while (p) {
		if (p == c)return false;
		p = p->parent;
	}

	children.push_back(c);

	if (c->parent)c->parent->RemoveChild(c);

	c->parent = this;
	
	//Need c.transform

}

void GameObject::RemoveChild(GameObject* c)
{
	if (!c)
		return;
	for (int i = 0; i < children.size(); ++i) {
		if (children[i] == c)
			children.erase(children.begin() + 1);
	}
	c->parent = nullptr;
}

void GameObject::RenderM()
{
	
	//C_Transform* transform = this->transform;
	C_Transform* transform = (C_Transform*)GetComponent(Component::Type::Transform);

	if (mesh != nullptr) {

		mesh->textureID;//= App->dummy->textureID;
		float4x4 tempMat;
		if (renderMesh == true) {
			if (this->parent == nullptr) tempMat = transform->GetLocal();
			else {
				tempMat = parent->transform->GetGlobal()* transform->GetLocal();
			}

			/*if (animation != nullptr && animation->_animableMesh != nullptr) {
				animation->_animableMesh->meshRenderer(tempMat.Transposed(), TextureTypes::CHECKERS, tempMat);
			}
			else {
				mesh->meshRenderer(tempMat.Transposed(), TextureTypes::CHECKERS, tempMat);
			}*/
			mesh->meshRenderer(tempMat.Transposed(), TextureTypes::CHECKERS, tempMat);

		}

		if (renderAABB == true) {
			mesh->RenderAABB();
		}
	}
}

void GameObject::RenderGameM()
{

	//C_Transform* transform = this->transform;
	C_Transform* transform = (C_Transform*)GetComponent(Component::Type::Transform);

	if (mesh != nullptr) {

		mesh->textureID;//= App->dummy->textureID;
		float4x4 tempMat;
		if (renderMesh == true) {
			if (this->parent == nullptr) tempMat = transform->GetLocal();
			else {
				tempMat = parent->transform->GetGlobal() * transform->GetLocal();
			}
			/*if (animation != nullptr && animation->_animableMesh != nullptr) {

				animation->_animableMesh->meshRenderer(tempMat.Transposed(), TextureTypes::CHECKERS, tempMat);
			}
			else {
				mesh->meshRenderer(tempMat.Transposed(), TextureTypes::CHECKERS, tempMat);
			}*/
			mesh->meshRenderer(tempMat.Transposed(), TextureTypes::CHECKERS, tempMat);

		}

	}
}

void GameObject::UpdateAABB()
{

	float4x4 tempMat;

	if (this->parent == nullptr) tempMat = transform->GetLocal();
	else {
		tempMat = transform->GetLocal() * parent->transform->GetGlobal();
	}
	mesh->OBB_ = mesh->AABB_;
	//Why don't work with transposed?
	mesh->OBB_.Transform(tempMat);
	mesh->global_AABB.SetNegativeInfinity();
	mesh->global_AABB.Enclose(mesh->OBB_);
}

void GameObject::CollectChilds(std::vector<GameObject*>& vector)
{
	vector.push_back(this);
	for (uint i = 0; i < children.size(); i++)
		children[i]->CollectChilds(vector);
}

