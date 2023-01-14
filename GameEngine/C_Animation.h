#pragma once
#include "Globals.h"

#include "S_Component.h"


#include<vector>
#include<string>
#include <map>

#include "MathGeoLib.h"
using namespace std;

struct BoneInfo;
class M_Mesh;
class T_AnimationLoader;
class C_Animation : public Component
{

public:

	C_Animation(GameObject* gO);
	~C_Animation();



	void InspectorW() override;
private:

	std::vector<T_AnimationLoader*> animations_List;

	T_AnimationLoader* prevAnimation = nullptr;
	T_AnimationLoader* currentAnimation = nullptr;
	T_AnimationLoader* _anim;


public:

	bool playing = true;
	bool started = false;
	float time = 0.f;
	float speed = 1.f;

	bool channelsLinked = false;
	bool bonesLinked = false;
	bool drawBones = false;

	float blendTime = 0.f;
	float blendTimeDuration = 0.f;
	float prevAnimTime = 0.0f;

	unsigned int prevAnimationX = 0;
	unsigned int currentAnimationX = 0;

	uint currentTimeAnimation = 0;
	uint previousTimeAnimation = 0;


	GameObject* rootBone = nullptr;
	map<string, GameObject*> boneMapping;


	M_Mesh* _animableMesh = nullptr;



	void DuplicateMeshintoAnimable();
	void MoveVerticesnNormals();
	static void RegenerateBuffers(M_Mesh* _animableMesh);

	void LinkChannelBones(GameObject* gameObject);
	void StoreBoneMapping(GameObject* gameObject);
	void GetBoneMapping(std::map<std::string, GameObject*>& boneMapping);
	float4x4 CalculateDeltaMatrix(float4x4 globalMat, float4x4 invertMat);


	void Start();
	void Update(float dt);
	void Pause();
	void Resume();


	void UpdateChannelsTransform(const T_AnimationLoader* settings, const T_AnimationLoader* blend, float blendRatio);
	void UpdateMeshAnimation(GameObject* gameObject);

	float3 GetChannelPosition(const BoneInfo& channel, float currentKey, float3 defaultPos) const;
	float3 GetChannelRotation(const BoneInfo& channel, float currentKey, float3 defaultRotation) const;
	float3 GetChannelScale(const BoneInfo& channel, float currentKey, float3 defaultScale) const;



};

