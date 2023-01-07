#include "C_Animation.h"
#include "T_AnimationLoader.h"
#include "S_GameObject.h"
#include "C_Transform.h"
C_Animation::C_Animation(GameObject* gO) : Component(gO)
{

	gameObject = gO;
	animations_List = gO->animations;
}

C_Animation::~C_Animation()
{}

void C_Animation::InspectorW()
{

	if (ImGui::CollapsingHeader("Animation", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::TextWrapped("Actual animation duration: "); ImGui::SameLine();

		ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(animations_List[0]->duration).c_str());
		
		ImGui::TextWrapped("Ticks per second: "); ImGui::SameLine();

		ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(gameObject->animations[0]->ticksPerSecond).c_str());

	}








}

void C_Animation::LinkChannelBones(GameObject* gameObject)
{
}

void C_Animation::StoreBoneMapping(GameObject* gameObject)
{
}

void C_Animation::Start()
{
	rootBone = gameObject->children[1]->children[0];

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

		UpdateChannelsTransform(currentAnimation, blendRatio > 0.0f ? prevAnimation : nullptr, blendRatio);
		UpdateMeshAnimation(gameObject->children[0]);
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
	for (boneIt = boneMapping.begin(); boneIt != boneMapping.end(); ++boneIt)
	{
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
	//float3 rotation = defaultRotation;

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
