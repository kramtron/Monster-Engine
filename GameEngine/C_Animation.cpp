#include "C_Animation.h"
#include "T_AnimationLoader.h"
#include "S_GameObject.h"
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
