#pragma once
#include "R_Mesh.h"


#include "cimport.h"
#include "scene.h"
#include "postprocess.h"


class MeshLoader : public M_Mesh
{
public:
	MeshLoader();
	~MeshLoader();


	static void StartDebugMode();
	static void StopDebugMode();
	
	static void LoadMesh(aiMesh* importedMesh);

private:

	


};


