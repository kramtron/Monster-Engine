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

	//MeshLoader::LoadFile("Assets/columna.fbx");
	GameObject* gO = new GameObject("BakerHouse", nullptr, "first", MeshLoader::LoadFile("Assets/BakerHouse.fbx"));
	//TextureLoader::LoadTexture("Assets/Baker_house.png");
	return ret;

}

bool ModuleDummy::CleanUp()
{

	LOGT(ConsoleType::SYSTEM, "cleaning test");


	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{



	


	/*ImGui::Begin("Hardware");
	//Colocar info del hardware aquí
	ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
	ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
	ImGui::Text("OpenGL version supported %s", glGetString(GL_VERSION));
	ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	ImGui::End();
	*/
	
	//Al crear una window nueva en caso de no poder mover con el mouse la window ir a imgui.ini y colocar al final DockId=0x8B93E3BD,1 (mientras tenga un dock debería poderse mover)

	


	
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

	return UPDATE_CONTINUE;
}