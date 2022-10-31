#include "T_MeshLoader.h"
#include "Globals.h"
#include "Application.h"


vector<M_Mesh*> M_Mesh::meshes;

GameObject* MeshLoader::gameObjectReturned = nullptr;

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
	const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {


		M_Mesh* our_mesh = new M_Mesh();

			for (uint i = 0; i < scene->mNumMeshes; i++) {

				our_mesh = MeshLoader::LoadMesh(scene->mMeshes[i]);
				

			}
			//Esto fuera o no renderiza si un fbx tiene mas de 1 objeto dentro
			meshes.push_back(our_mesh);
			return our_mesh;

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

	//GameObject* our_mesh = new GameObject();
	
	our_mesh->num_vertices = importedMesh->mNumVertices;
	our_mesh->vertices = new float[our_mesh->num_vertices * 5];

	memcpy(our_mesh->vertices, importedMesh->mVertices, sizeof(float) * our_mesh->num_vertices * 3);



	for (int v = 0; v < our_mesh->num_vertices; v++) {
		//vertices
		our_mesh->vertices[v * VERTEX_ARGUMENTS] = importedMesh->mVertices[v].x;
		our_mesh->vertices[v * VERTEX_ARGUMENTS + 1] = importedMesh->mVertices[v].y;
		our_mesh->vertices[v * VERTEX_ARGUMENTS + 2] = importedMesh->mVertices[v].z;

		//uvs
		our_mesh->vertices[v * VERTEX_ARGUMENTS + 3] = importedMesh->mTextureCoords[0][v].x;
		our_mesh->vertices[v * VERTEX_ARGUMENTS + 4] = 1 - importedMesh->mTextureCoords[0][v].y;	//TODO: be careful INVERTING UVS
	}





	LOG("new mesh with %d vertices", our_mesh->num_vertices);
	


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
				
				
			}
		}

	}

	


	glGenBuffers(1, (GLuint*)&(our_mesh->id_vertices));
	glGenBuffers(1, (GLuint*)&(our_mesh->id_indices));


	//Bind and fill buffers
	glBindBuffer(GL_ARRAY_BUFFER, our_mesh->id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * our_mesh->num_vertices * VERTEX_ARGUMENTS, our_mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, our_mesh->id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * our_mesh->num_indices, our_mesh->indices, GL_STATIC_DRAW);

	//Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);

	

	return our_mesh;

}

void MeshLoader::Renderer()
{
	/*for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->meshRenderer();
	} */
}

void MeshLoader::CleanUp()
{
	for (int i = 0; i < meshes.size(); i++) {
		delete meshes[i]; //Algo aquí hace que salte error en delete[num_vertices] // 12/10 parece que ya no pero igual es problema a futuro
		meshes[i] = nullptr;
	}
	meshes.clear();


}


