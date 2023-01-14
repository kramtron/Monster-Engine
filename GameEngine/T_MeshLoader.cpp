#include "T_MeshLoader.h"
#include "Globals.h"
#include "Application.h"
#include "T_FileInfo.h"
#include "ModuleRenderer3D.h"
#include "T_AnimationLoader.h"



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


M_Mesh* MeshLoader::LoadFile(string file_path, GameObject* parent = nullptr)
{
	
	const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate);

	if (scene != nullptr && scene->HasMeshes()) {

		std::vector<T_AnimationLoader*> animationList;
		T_AnimationLoader* tempA = new T_AnimationLoader();

		M_Mesh* our_mesh;
		
		if (scene->HasAnimations()) {

			for (unsigned int i = 0; i < scene->mNumAnimations; i++) {

				aiAnimation* animation = scene->mAnimations[i];
				//Caragr en lista 
				animationList.push_back(tempA->LoadAnimation(animation) );
			}

		}

			aiMatrix4x4 matrix;
			aiIdentityMatrix4(&matrix);
			//our_mesh = MeshLoader::LoadMesh(scene->mRootNode);
			our_mesh = MeshLoader::LoadMeshNode(scene,scene->mRootNode,parent,file_path.c_str(),matrix);

			//Here add the animation to the game object
			//parent->children[0]->animations = animationList;
			T_AnimationLoader::SetAnimationOnGameObjectRoot(scene->mAnimations, animationList, parent->children[0]->children[0]);

			return our_mesh;

		aiReleaseImport(scene);
		delete tempA;

	}
	else {
		LOG("Error loading scene %s", file_path);
	}
	
}

string MeshLoader::ImportTexture(const aiScene* scene, uint mesh_index, const char* file_path)
{
	if (scene->HasMaterials() && scene->mMaterials[scene->mMeshes[mesh_index]->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		
		aiString texture_path;
		scene->mMaterials[scene->mMeshes[mesh_index]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path);
		scene->mMaterials[scene->mMeshes[mesh_index]->mMaterialIndex]->mProperties[0];
		File Path1(file_path);
		File texturePath(texture_path.C_Str());

		string finalPath = Path1.path;
		uint assetPos = finalPath.find("Assets/");
		finalPath = finalPath.substr(assetPos, finalPath.find_last_of("/") - assetPos);
		finalPath.append("/").append(texturePath.name);

		return finalPath;
	}

	return "";
}




M_Mesh* MeshLoader::LoadMesh(aiMesh* importedMesh)
{


	
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
		if (importedMesh->mTextureCoords[0] == nullptr) continue;
 		our_mesh->vertices[v * VERTEX_ARGUMENTS + 3] = importedMesh->mTextureCoords[0][v].x;
		our_mesh->vertices[v * VERTEX_ARGUMENTS + 4] = importedMesh->mTextureCoords[0][v].y;	
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

		our_mesh->InitAABB();

	}
	if (importedMesh->HasBones()) {
		our_mesh->hasSkeleton = true;
		LoadBones(importedMesh, our_mesh);
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(1, (GLuint*)&(our_mesh->id_vertices));
	glGenBuffers(1, (GLuint*)&(our_mesh->id_indices));


	//Bind and fill buffers
	glBindBuffer(GL_ARRAY_BUFFER, our_mesh->id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * our_mesh->num_vertices * VERTEX_ARGUMENTS, our_mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, our_mesh->id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * our_mesh->num_indices, our_mesh->indices, GL_STATIC_DRAW);

	//Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);

	
	meshes.push_back(our_mesh);

	
	
	return our_mesh;

}

M_Mesh* MeshLoader::LoadMeshNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* file_path, aiMatrix4x4 transform)
{

	if (node->mNumMeshes == 0 && node->mNumChildren == 0) return nullptr;

	

	GameObject* gO = new GameObject(node->mName.C_Str(), parent, "none");


	aiMatrix4x4 tempMat = node->mTransformation;
	aiVector3D position, scale, rotation;
	aiQuaternion qrot;
	tempMat.Decompose(scale, qrot, position);
	rotation = qrot.GetEuler();

	gO->transform->scale = float3(scale.x, scale.y, scale.z);
	gO->transform->rotation = (float3(rotation.x * RADTODEG, rotation.y * RADTODEG, rotation.z * RADTODEG));
	gO->transform->position = (float3(position.x,  position.z, position.y));
	//gO->transform->ResetTransform();

	gO->transform->TransformToUpdate();


	if (node->mNumMeshes != 0)
	{
	
		string texturePath = "";

		for (int i = 0; i < node->mNumMeshes; i++) {
		

			M_Mesh* our_mesh = LoadMesh(scene->mMeshes[node->mMeshes[i]]);
			our_mesh->myGO = gO;
			gO->mesh = our_mesh;
			gO->meshR = (C_Mesh*)gO->AddComponent(Component::Type::Mesh);
			

		
			if (our_mesh == nullptr) {
				LOG( "WARNING, loading scene %s, a mesh has no faces.", file_path);
				continue;
			}

			if (texturePath == "") texturePath = ImportTexture(scene, node->mMeshes[i], file_path);

			
			if (texturePath != "") {

				gO->mesh->textureID = TextureLoader::LoadTexture(texturePath.c_str());
			}
		}

		
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		LoadMeshNode(scene, node->mChildren[i],gO, file_path,tempMat);
	}
	return nullptr;
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

void MeshLoader::LoadBones(const aiMesh* importedMesh, M_Mesh* ourMesh)
{

	ourMesh->bonesTransforms.resize(importedMesh->mNumBones);

	ourMesh->bones_count = importedMesh->mNumVertices * 4;
	ourMesh->bones = new int[ourMesh->bones_count];
	for (int i = 0; i < ourMesh->bones_count; i++)
	{
		ourMesh->bones[i] = -1;
	}

	//Set the weights array each 4
	ourMesh->weights_count = importedMesh->mNumVertices * 4;
	ourMesh->boneWeights = new float[ourMesh->weights_count];
	for (int i = 0; i < ourMesh->weights_count; i++)
	{
		ourMesh->boneWeights[i] = 0.f;
	}



	for (int boneIndex = 0; boneIndex < importedMesh->mNumBones; boneIndex++)
	{
		aiBone* bone = importedMesh->mBones[boneIndex];
		ourMesh->bonesMap[bone->mName.C_Str()] = boneIndex;

	
		float4x4 offset = float4x4(bone->mOffsetMatrix.a1, bone->mOffsetMatrix.a2, bone->mOffsetMatrix.a3, bone->mOffsetMatrix.a4,
			bone->mOffsetMatrix.b1, bone->mOffsetMatrix.b2, bone->mOffsetMatrix.b3, bone->mOffsetMatrix.b4,
			bone->mOffsetMatrix.c1, bone->mOffsetMatrix.c2, bone->mOffsetMatrix.c3, bone->mOffsetMatrix.c4,
			bone->mOffsetMatrix.d1, bone->mOffsetMatrix.d2, bone->mOffsetMatrix.d3, bone->mOffsetMatrix.d4);

		ourMesh->bonesOffsets.push_back(offset);

	
		for (int i = 0; i < bone->mNumWeights; ++i)
		{
			uint index = bone->mWeights[i].mVertexId;
			
			for (int j = 0; j < 4; ++j)
			{
				if (ourMesh->bones[index * 4 + j] == -1)
				{
					ourMesh->bones[index * 4 + j] = boneIndex;
					ourMesh->boneWeights[index * 4 + j] = bone->mWeights[i].mWeight;
					break;
				}
			}
		}

	}


}


