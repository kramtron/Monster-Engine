#include "S_Component.h"

Component::Component(GameObject* gameObject)
{
}

Component::~Component()
{
}

void Component::Enable()
{
	active = true;
}

void Component::Disable()
{
	active = false;
}
