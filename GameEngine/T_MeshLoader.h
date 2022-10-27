#pragma once

#include "R_Mesh.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

using namespace std;

class GameObject;
//class M_Mesh;

class MeshLoader : public M_Mesh {
public:
	MeshLoader();
	~MeshLoader();


	static void StartDebugMode();
	static void StopDebugMode();
	
	static M_Mesh* LoadMesh(aiMesh* importedMesh);
	static M_Mesh* LoadFile(string file_path);

	static void Renderer();
	static void CleanUp();


	static GameObject* gameObjectReturned;

private:

	


};


