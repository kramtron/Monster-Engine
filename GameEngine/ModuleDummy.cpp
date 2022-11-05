#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "glew.h"

#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "T_TextureLoader.h"
#include "ImHierarchyWindow.h"

ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleDummy::~ModuleDummy()
{

}

bool ModuleDummy::Start()
{
	LOG("Testing");
	bool ret = true;

	textureID= TextureLoader::LoadTexture("Assets/Baker_house.png");

	return ret;

}

bool ModuleDummy::CleanUp()
{

	LOGT(ConsoleType::SYSTEM, "cleaning test");

	/*for (uint i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
		gameObjects[i] = nullptr;
	}*/

	gameObjects.clear();


	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{



	


	

	


	
	return UPDATE_CONTINUE;

}

int ModuleDummy::AddGameObject(GameObject* gO)
{

	//Add in GameObject Tree
	gameObjects[IDCounter] = gO;

	return IDCounter++;
}

update_status ModuleDummy::PostUpdate(float dt)
{
	

	
	

	if (wireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (exit) {

		return UPDATE_STOP;

	}

	return UPDATE_CONTINUE;
}