#include "T_AnimationLoader.h"







std::map<double, float3>::const_iterator BoneInfo::GetPrevPosKey(double currentKey) const
{
	std::map<double, float3>::const_iterator ret = positionKeys.lower_bound(currentKey);
	if (ret != positionKeys.begin())
		ret--;

	return ret;
}

std::map<double, float3>::const_iterator BoneInfo::GetNextPosKey(double currentKey) const
{
	return positionKeys.upper_bound(currentKey);
}

std::map<double, float3>::const_iterator BoneInfo::GetPrevRotKey(double currentKey) const
{
	std::map<double, float3>::const_iterator ret = rotationKeys.lower_bound(currentKey);
	if (ret != rotationKeys.begin())
		ret--;
	return ret;
}

std::map<double, float3>::const_iterator BoneInfo::GetNextRotKey(double currentKey) const
{
	return rotationKeys.upper_bound(currentKey);
}

std::map<double, float3>::const_iterator BoneInfo::GetPrevScaleKey(double currentKey) const
{
	std::map<double, float3>::const_iterator ret = scaleKeys.lower_bound(currentKey);
	if (ret != scaleKeys.begin())
		ret--;
	return ret;
}

std::map<double, float3>::const_iterator BoneInfo::GetNextScaleKey(double currentKey) const
{
	return scaleKeys.upper_bound(currentKey);
}













T_AnimationLoader::T_AnimationLoader()
{
}

T_AnimationLoader::~T_AnimationLoader()
{
}

T_AnimationLoader* T_AnimationLoader::LoadAnimation(aiAnimation* importedAnimation)
{
	
	uint UID = 0;

	
	
	/*std::string file = ANIMATIONS_PATH;
	file += std::to_string(UID);
	file += ".anim";*/



	T_AnimationLoader* animation= new T_AnimationLoader();

	animation->ticksPerSecond = importedAnimation->mTicksPerSecond;
	animation->duration = importedAnimation->mDuration;

	for (int i = 0; i < importedAnimation->mNumChannels; i++)
	{
		BoneInfo bInfo;

		bInfo.name = importedAnimation->mChannels[i]->mNodeName.C_Str();
		uint pos = bInfo.name.find("_$AssimpFbx$_");
		if (pos != std::string::npos)
		{
			bInfo.name = bInfo.name.substr(0, pos);
		}
		for (int j = 0; j < importedAnimation->mChannels[i]->mNumPositionKeys; j++)
		{
			aiVector3t<float> aiValue = importedAnimation->mChannels[i]->mPositionKeys[j].mValue;
			float3 positionKey = float3(aiValue.x, aiValue.y, aiValue.z);

			bInfo.positionKeys[importedAnimation->mChannels[i]->mPositionKeys[j].mTime] = positionKey;

		}
		for (int j = 0; j < importedAnimation->mChannels[i]->mNumRotationKeys; j++)
		{
			aiQuaterniont<float> aiValue = importedAnimation->mChannels[i]->mRotationKeys[j].mValue;
			Quat q = Quat(aiValue.x, aiValue.y, aiValue.z, aiValue.w);

			float3 rotationKey;
			{
				// X
				double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
				double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
				rotationKey.x = std::atan2(sinr_cosp, cosr_cosp);

				// Y
				double sinp = std::sqrt(1 + 2 * (q.w * q.x - q.y * q.z));
				double cosp = std::sqrt(1 - 2 * (q.w * q.x - q.y * q.z));
				rotationKey.y = 2 * std::atan2(sinp, cosp) - pi / 2;

				// Z
				double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
				double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
				rotationKey.z = std::atan2(siny_cosp, cosy_cosp);
			}
			bInfo.rotationKeys[importedAnimation->mChannels[i]->mRotationKeys[j].mTime] = rotationKey;
		}

		for (int j = 0; j < importedAnimation->mChannels[i]->mNumScalingKeys; j++)
		{
			aiVector3t<float> aiValue = importedAnimation->mChannels[i]->mScalingKeys[j].mValue;
			float3 scaleKey = float3(aiValue.x, aiValue.y, aiValue.z);

			bInfo.scaleKeys[importedAnimation->mChannels[i]->mScalingKeys[j].mTime] = scaleKey;
		}
		animation->bones[bInfo.name] = bInfo;
	}



	/*char* buffer;
	uint size = animation->SaveCustomFormat(animation, &buffer);

	RELEASE_ARRAY(buffer);*/



	return animation;



}

uint T_AnimationLoader::SaveCustomFormat(T_AnimationLoader* animation, char** buffer)
{

	uint size = sizeof(float) + sizeof(float) + sizeof(uint);


	//Channels size 
	std::map<std::string,BoneInfo>::const_iterator it;
	for (it = animation->bones.begin(); it != animation->bones.end(); ++it)
		size += T_AnimationLoader::GetBonesSize(it->second);


	//Allocate buffer size
	*buffer = new char[size];
	char* cursor = *buffer;

	//Duration
	memcpy(cursor, &animation->duration, sizeof(float));
	cursor += sizeof(float);

	//Ticks per second
	memcpy(cursor, &animation->ticksPerSecond, sizeof(float));
	cursor += sizeof(float);

	//Channels number
	uint channelsSize = animation->bones.size();
	memcpy(cursor, &channelsSize, sizeof(uint));
	cursor += sizeof(uint);

	//Save each channel data
	for (it = animation->bones.begin(); it != animation->bones.end(); ++it)
		T_AnimationLoader::SaveBones(it->second, &cursor);


	

	return size;




	
}

uint T_AnimationLoader::GetBonesSize(const BoneInfo& bone)
{

	uint ret = sizeof(uint) + bone.name.size() + sizeof(uint) * 3;
	//Translation
	ret += sizeof(double) * bone.positionKeys.size() + sizeof(float) * bone.positionKeys.size() * 3;
	//Rotation
	ret += sizeof(double) * bone.rotationKeys.size() + sizeof(float) * bone.rotationKeys.size() * 4;
	//Scale
	ret += sizeof(double) * bone.scaleKeys.size() + sizeof(float) * bone.scaleKeys.size() * 3;

	return ret;
}

void T_AnimationLoader::SaveBones(const BoneInfo& bone, char** cursor)
{

	uint nameSize = bone.name.size();
	memcpy(*cursor, &nameSize, sizeof(uint));
	*cursor += sizeof(uint);

	memcpy(*cursor, bone.name.c_str(), bone.name.size());
	*cursor += bone.name.size();

	//Ranges
	uint ranges[3] = { bone.positionKeys.size(), bone.rotationKeys.size(), bone.scaleKeys.size() };
	memcpy(*cursor, ranges, sizeof(uint) * 3);
	*cursor += sizeof(uint) * 3;

	//Save each channel, depending on float or quat based
	
	SaveBoneKey(bone.positionKeys, cursor);
	SaveBoneKey(bone.rotationKeys, cursor);
	SaveBoneKey(bone.scaleKeys, cursor);


}

void T_AnimationLoader::SaveBoneKey(const std::map<double, float3>& map, char** cursor)
{
	std::map<double, float3>::const_iterator it = map.begin();
	for (it = map.begin(); it != map.end(); it++)
	{
		memcpy(*cursor, &it->first, sizeof(double));
		*cursor += sizeof(double);

		memcpy(*cursor, &it->second, sizeof(float) * 3);
		*cursor += sizeof(float) * 3;
	}
}
void T_AnimationLoader::SaveBoneKey(const std::map<double, Quat>& map, char** cursor) 
{

	std::map<double, Quat>::const_iterator it = map.begin();
	for (it = map.begin(); it != map.end(); it++)
	{
		memcpy(*cursor, &it->first, sizeof(double));
		*cursor += sizeof(double);

		memcpy(*cursor, &it->second, sizeof(float) * 4);
		*cursor += sizeof(float) * 4;
	}
}

