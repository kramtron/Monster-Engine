#include "C_Animation.h"
#include "T_AnimationLoader.h"
#include "S_GameObject.h"
#include "C_Transform.h"
C_Animation::C_Animation(GameObject* gO) : Component(gO)
{

	gameObject = gO;
	/*animations_List = gO->animations;*/
}

C_Animation::~C_Animation()
{}

void C_Animation::InspectorW()
{

	if (ImGui::CollapsingHeader("Animation", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::TextWrapped("Actual animation duration: "); ImGui::SameLine();

		ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(animations_List[0]->duration).c_str());
		
		ImGui::TextWrapped("Ticks per second: "); ImGui::SameLine();

		ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(animations_List[0]->ticksPerSecond).c_str());

	}

}

void C_Animation::DuplicateMeshintoAnimable()
{

	bool duplicateMesh = false;

	if (_animableMesh == nullptr && gameObject->mesh != nullptr)
	{
		duplicateMesh = true;
		_animableMesh = new M_Mesh;
		//Get the current mesh
		M_Mesh* our_mesh = gameObject->mesh;



		_animableMesh->num_indices = our_mesh->num_indices;
		_animableMesh->num_vertices = our_mesh->num_vertices;
		
		_animableMesh->indices = new uint[our_mesh->num_indices];
		_animableMesh->vertices = new float[our_mesh->num_vertices * 3];


		memcpy(_animableMesh->indices,our_mesh->indices, our_mesh->num_indices * sizeof(uint));

		memset(_animableMesh->vertices, 0, _animableMesh->num_vertices * sizeof(float) * 3);

	}



	if (duplicateMesh) {
		//_animableMesh->RegenerateBuffers(true); 
		//TODUWU
		RegenerateBuffers(_animableMesh,true);
	}
}

void C_Animation::MoveVerticesnNormals()
{

	M_Mesh* our_mesh = gameObject->mesh;

	std::map<std::string, GameObject*> bonesMap;
	GetBoneMapping(bonesMap);

	std::vector<float4x4> boneTransforms;
	boneTransforms.resize(our_mesh->bonesOffsets.size());


	for (std::map<std::string, uint>::iterator it = our_mesh->bonesMap.begin(); it != our_mesh->bonesMap.end(); ++it)
	{
		GameObject* bone = bonesMap[it->first];

		if (bone != nullptr) {

			float4x4 Delta = CalculateDeltaMatrix(dynamic_cast<C_Transform*>(bone->GetComponent(Component::Type::Transform))->GetGlobal(), dynamic_cast<C_Transform*>(gameObject->GetComponent(Component::Type::Transform))->GetGlobal().Inverted());
			Delta = Delta * our_mesh->bonesOffsets[it->second];
			boneTransforms[it->second] = Delta;
		}
	}

	
	for (uint v = 0; v < our_mesh->num_vertices; ++v) {


		for (uint b = 0; b < 4; ++b) {


			int bone_ID = our_mesh->bones[v * 4 + b];
			float boneWeight = our_mesh->boneWeights[v * 4 + b];


			if (bone_ID == -1) continue;

			float3 Inc = boneTransforms[bone_ID].TransformPos(float3(&our_mesh->vertices[v * 3]));

			_animableMesh->vertices[v * 3] += Inc.x * boneWeight;
			_animableMesh->vertices[v * 3 + 1] += Inc.y * boneWeight;
			_animableMesh->vertices[v * 3 + 2] += Inc.z * boneWeight;


		}

	}

	RegenerateBuffers(_animableMesh);
}

void C_Animation::RegenerateBuffers(M_Mesh* _animableMesh, bool init)
{

	if (init) {

		//Vertex
		glGenBuffers(1, (GLuint*)&(_animableMesh->id_vertices));


		//Index
		glGenBuffers(1, (GLuint*)&(_animableMesh->id_indices));


		//Bind and fill buffers


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _animableMesh->id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * _animableMesh->num_indices, _animableMesh->indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _animableMesh->id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _animableMesh->num_vertices * 3, &_animableMesh->vertices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void C_Animation::LinkChannelBones(GameObject* gameObject)
{
	for (int i = 0; i < gameObject->children.size(); i++) {
		if (_anim->bones.find(gameObject->children[i]->name) != _anim->bones.end()) {
			rootBone = gameObject->children[i];
			channelsLinked = true;
			StoreBoneMapping(gameObject);
		}
		LinkChannelBones(gameObject->children[i]);
	}

}

void C_Animation::StoreBoneMapping(GameObject* gameObject)
{
	boneMapping[gameObject->name] = gameObject;
	for (int i = 0; i < gameObject->children.size(); i++)
	{
		StoreBoneMapping(gameObject->children[i]);
	}
}

void C_Animation::GetBoneMapping(std::map<std::string, GameObject*>& boneMapping)
{

	boneMapping.clear();
	std::vector<GameObject*> gameObjects;
	rootBone->CollectChilds(gameObjects);

	for (uint i = 0; i < gameObjects.size(); ++i)
	{
		boneMapping[gameObjects[i]->name] = gameObjects[i];
	}


}

float4x4 C_Animation::CalculateDeltaMatrix(float4x4 globalMat, float4x4 invertMat)
{
	float3 position;
	Quat rotation;
	float3 scale;


	float4x4 mat = globalMat;
	mat.Decompose(position, rotation, scale);
	mat = dynamic_cast<C_Transform*>(gameObject->GetComponent(Component::Type::Transform))->GetGlobal().Inverted() * mat;
	mat.Decompose(position, rotation, scale);

	return mat;

}

void C_Animation::Start()
{
	rootBone = gameObject->parent->children[1]->children[0];

	if (rootBone == nullptr) return;

	boneMapping.clear();

	std::vector<GameObject*> bones;
	rootBone->CollectChilds(bones);

	for (uint i = 0; i < bones.size(); ++i)
	{
		boneMapping[bones[i]->name] = bones[i];
	}

	currentAnimation =  animations_List[0];
	started = true;
}

void C_Animation::Update(float dt)
{

	if (playing == true) {
		if (started == false) {
			Start();
		}

		/*if (EngineExternal->moduleInput->GetKey(SDL_SCANCODE_2) == KEY_STATE::KEY_DOWN) {
			time = 0.f;
			currentAnimation = animations_List[1];
		}
		else if (EngineExternal->moduleInput->GetKey(SDL_SCANCODE_2) == KEY_STATE::KEY_REPEAT) {
			currentAnimation = animations_List[1];
		}
		else if (EngineExternal->moduleInput->GetKey(SDL_SCANCODE_2) == KEY_STATE::KEY_UP) {
			time = 0.f;
			currentAnimation = animations_List[0];
		}

		if (EngineExternal->moduleInput->GetKey(SDL_SCANCODE_1) == KEY_STATE::KEY_DOWN) {
			time = 0.f;
			currentAnimation = animations_List[2];
		}*/
		

		float blendRatio = 0.0f;
		if (blendTimeDuration > 0.0f)
		{
			prevAnimTime += dt;
			previousTimeAnimation = time * prevAnimation->ticksPerSecond;
			previousTimeAnimation += prevAnimation->initTimeAnim;
			blendTime += dt;

			if (blendTime >= blendTimeDuration)
			{
				blendTimeDuration = 0.0f;
			}
			else if (prevAnimation && prevAnimTime >= prevAnimation->duration)
			{
				if (prevAnimation->loopable == true)
				{
					prevAnimTime = 0.0f;
					
				}
			}

			if (blendTimeDuration > 0.0f)
				blendRatio = blendTime / blendTimeDuration;
		}
		

		time += dt;
		currentTimeAnimation = time * currentAnimation->ticksPerSecond;
		currentTimeAnimation += currentAnimation->initTimeAnim;
		if (currentAnimation && currentTimeAnimation >= currentAnimation->duration) {
			if (currentAnimation->loopable == true) {
				time = 0.f;
			}
			else {
				currentAnimation = animations_List[0];
				time = 0.f;
				return;
			}
		}
		LOG("sdfkjhda");
		UpdateChannelsTransform(currentAnimation, blendRatio > 0.0f ? prevAnimation : nullptr, blendRatio);
		UpdateMeshAnimation(gameObject);
		std::vector<GameObject*> bones;
		rootBone->CollectChilds(bones);
		//DrawBones(bones[0]);

	}


}

void C_Animation::UpdateChannelsTransform(const T_AnimationLoader* settings, const T_AnimationLoader* blend, float blendRatio)
{

	uint currentFrame = currentTimeAnimation;

	uint prevBlendFrame = 0;
	if (blend != nullptr)
	{
		prevBlendFrame = blend->ticksPerSecond * prevAnimTime;
	}
	
	std::map<std::string, GameObject*>::iterator boneIt;
	int pass=0;
	for (boneIt = boneMapping.begin(); boneIt != boneMapping.end(); ++boneIt)
	{
		LOG("Pass %d", pass++);
		C_Transform* transform = dynamic_cast<C_Transform*>(boneIt->second->GetComponent(Component::Type::Transform));

		if (settings->bones.find(boneIt->first.c_str()) == settings->bones.end()) continue;

		const BoneInfo& channel = settings->bones.find(boneIt->first.c_str())->second;

		float3 position = GetChannelPosition(channel, currentFrame, transform->position);
		float3 rotation = GetChannelRotation(channel, currentFrame, transform->rotation);
		float3 scale = GetChannelScale(channel, currentFrame, transform->scale);


		if (blend != nullptr)
		{
			const BoneInfo& blendChannel = blend->bones.find(boneIt->first.c_str())->second;

			position = float3::Lerp(GetChannelPosition(blendChannel, prevBlendFrame, transform->position), position, blendRatio);
			rotation = float3::Lerp(GetChannelRotation(blendChannel, prevBlendFrame, transform->rotation), rotation, blendRatio);
			scale = float3::Lerp(GetChannelScale(blendChannel, prevBlendFrame, transform->scale), scale, blendRatio);
		}


		transform->position = position;
		transform->rotation = rotation * RADTODEG;
		transform->scale = scale;
		transform->TransformToUpdate();
	}




}

void C_Animation::UpdateMeshAnimation(GameObject* gameObject)
{
	

	if (gameObject->mesh != nullptr)
	{
		DuplicateMeshintoAnimable();
		MoveVerticesnNormals();
	}

}

float3 C_Animation::GetChannelPosition(const BoneInfo& channel, float currentKey, float3 defaultPos) const
{
	if (channel.positionKeys.size() > 0)
	{
		std::map<double, float3>::const_iterator previous = channel.GetPrevPosKey(currentKey);
		std::map<double, float3>::const_iterator next = channel.GetNextPosKey(currentKey);

		if (channel.positionKeys.begin()->first == -1) {
			return defaultPos;
		}

		// Check Blending Ratio between Keys
		if (previous == next) {
			defaultPos = previous->second;
		}
		else
		{
			float ratio = (currentKey - previous->first) / (next->first - previous->first);
			defaultPos = previous->second.Lerp(next->second, ratio);
		}
	}

	return defaultPos;
}

float3 C_Animation::GetChannelRotation(const BoneInfo& channel, float currentKey, float3 defaultRotation) const
{
	float3 rotation = defaultRotation;

	if (channel.rotationKeys.size() > 0)
	{
		std::map<double, float3>::const_iterator previous = channel.GetPrevRotKey(currentKey);
		std::map<double, float3>::const_iterator next = channel.GetNextRotKey(currentKey);

		if (channel.rotationKeys.begin()->first == -1) return defaultRotation;

		if (next == channel.rotationKeys.end())
			next = previous;

		//If both keys are the same, no need to blend
		if (previous == next)
			defaultRotation = previous->second;
		else //blend between both keys
		{
			//0 to 1
		float ratio = (currentKey - previous->first) / (next->first - previous->first);
			defaultRotation = previous->second.Lerp(next->second, ratio);

			//// Linearly interpolate the rotation angles
			//rotation.x = Lerp(previous->second.x, next->second.x, ratio);
			//rotation.y = Lerp(previous->second.y, next->second.y, ratio);
			//rotation.z = Lerp(previous->second.z, next->second.z, ratio);
		}
	}
	return defaultRotation;


	


}

float3 C_Animation::GetChannelScale(const BoneInfo& channel, float currentKey, float3 defaultScale) const
{
	if (channel.scaleKeys.size() > 0)
	{
		std::map<double, float3>::const_iterator previous = channel.GetPrevScaleKey(currentKey);
		std::map<double, float3>::const_iterator next = channel.GetPrevScaleKey(currentKey);

		if (channel.scaleKeys.begin()->first == -1) {
			return defaultScale;
		}

		// Check Blending Ratio between Keys
		if (previous == next)
		{
			defaultScale = previous->second;
		}
		else
		{
			float ratio = (currentKey - previous->first) / (next->first - previous->first);
			defaultScale = previous->second.Lerp(next->second, ratio);
		}
	}
	return defaultScale;
}

void C_Animation::SetResource(T_AnimationLoader* re_anim)
{
	if (_anim != nullptr) {
		_anim = re_anim;

		SetAnimation(_anim);
	}

}

void C_Animation::SetAnimation(T_AnimationLoader* anim)
{

	_anim = anim;
	_anim->animationName = "Idle";
	_anim->initTimeAnim = 0;
	_anim->duration = 46;
	animations_List.push_back(_anim);

	T_AnimationLoader* run = new T_AnimationLoader(*_anim);
	run->animationName = "Run";
	run->initTimeAnim = 50;
	run->duration = 72;
	animations_List.push_back(run);


	T_AnimationLoader* attack = new T_AnimationLoader(*_anim);
	attack->animationName = "Attack";
	attack->initTimeAnim = 73;
	attack->duration = 120;
	attack->loopable = false;
	animations_List.push_back(attack);

}

void C_Animation::DrawBones(GameObject* gameObject)
{

	glColor3f(1.f, 0.f, 0.f);
	glLineWidth(4.f);
	glBegin(GL_LINES);

	//Draw lines
	std::map<std::string, GameObject*>::iterator bones;
	float3 position;
	Quat rotation;
	float3 scale;

	if (gameObject->parent != nullptr) {
		gameObject->parent->transform->globalTransform.Decompose(position, rotation, scale);
		glVertex3f(position.x, position.y, position.z);
	}
	gameObject->transform->globalTransform.Decompose(position, rotation, scale);
	glVertex3f(position.x, position.y, position.z);
	//LOG(LogType::L_NORMAL, "Name: %s  %f,%f,%f",bones->first.c_str(), position.x, position.y, position.z);
	if (gameObject->children.size() > 0) {
		for (uint i = 0; i < gameObject->children.size(); i++)
		{
			DrawBones(gameObject->children[i]);
		}
	}
	glEnd();
	glLineWidth(1.f);
	glColor3f(1.f, 1.f, 1.f);

}
