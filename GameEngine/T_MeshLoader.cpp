#include "T_MeshLoader.h"
#include "Globals.h"
#include "Application.h"

const aiScene* scene;

vector<M_Mesh*> M_Mesh::meshes;

MeshLoader::MeshLoader()
{
}

MeshLoader::~MeshLoader()
{
}

void MeshLoader::StartDebugMode()
{
	//Assimp debug
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void MeshLoader::StopDebugMode()
{
	//Clean logs assimp
	aiDetachAllLogStreams();
}


M_Mesh* MeshLoader::LoadFile(string file_path)
{
	 scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {


		if (scene->HasMeshes()) {
			for (uint i = 0; i < scene->mNumMeshes; i++) {
				meshes.push_back(MeshLoader::LoadMesh(scene->mMeshes[i]));

			}
		}

		aiReleaseImport(scene);
	}
	else {
		LOG("Error loading scene %s", file_path);
	}

	

	return nullptr;
}




M_Mesh* MeshLoader::LoadMesh(aiMesh* importedMesh)
{

	uint my_id = 0;
	uint my_indices = 0;
	




	M_Mesh* our_mesh = new M_Mesh();
	
	our_mesh->num_vertices = importedMesh->mNumVertices;
	our_mesh->vertices = new float[our_mesh->num_vertices * 3];

	memcpy(our_mesh->vertices, importedMesh->mVertices, sizeof(float) * our_mesh->num_vertices * 3);
	LOG("new mesh with %d vertices", our_mesh->num_vertices);
	/*glGenBuffers(1, (GLuint*)&(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id); // << THIS IS ACTUALLY NOT NECESSARY
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * our_mesh->num_vertices * 3, our_mesh->vertices, GL_STATIC_DRAW);*/


	if (importedMesh->HasFaces()) {
	
		our_mesh->num_indices = importedMesh->mNumFaces * 3;
		our_mesh->indices = new uint[our_mesh->num_indices]; // assume each face is a triangle
		for (uint i = 0; i < importedMesh->mNumFaces; ++i)
		{
			if (importedMesh->mFaces[i].mNumIndices != 3)
			{
				LOG("Warning, geometry face with != indices");
			}
			else
			{
				memcpy(&our_mesh->indices[i * 3], importedMesh->mFaces[i].mIndices, 3 * sizeof(uint));
				
				/*glGenBuffers(1, (GLuint*)&(my_indices));
				glBindBuffer(GL_ARRAY_BUFFER, my_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * our_mesh->num_indices, our_mesh->indices, GL_STATIC_DRAW);*/
			}
		}

	}

	return our_mesh;

}

void MeshLoader::Renderer()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->meshRenderer();
	}
}

void MeshLoader::CleanUp()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->~M_Mesh();
		//delete meshes[i]; //Algo aquí hace que salte error en delete[num_vertices]
	}
	meshes.clear();

	//delete(scene);
	//delete(meshes);

}


