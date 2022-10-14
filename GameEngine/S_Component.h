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

	void Update(float dt);




	Type type;


protected:

	bool active = false;
	const char* name;














};

