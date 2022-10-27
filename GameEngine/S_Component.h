#pragma once


class GameObject;

class Component
{
public:
	enum class Type {

		Transform,
		Mesh,
		Material,
		Light,
		None,

	};


	Component(GameObject* gameObject);
	~Component();

	void Enable();
	void Disable();

	bool isEnable() { return active; };

	void Update(float dt) {};


	virtual void InspectorW() {};

	Type type = Type::None;


protected:

	bool active = false;














};

