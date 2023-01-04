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

std::map<double, Quat>::const_iterator BoneInfo::GetPrevRotKey(double currentKey) const
{
	std::map<double, Quat>::const_iterator ret = rotationKeys.lower_bound(currentKey);
	if (ret != rotationKeys.begin())
		ret--;
	return ret;
}

std::map<double, Quat>::const_iterator BoneInfo::GetNextRotKey(double currentKey) const
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

uint T_AnimationLoader::SaveCustomFormat(T_AnimationLoader* animation, char** buffer)
{

	uint size = sizeof(float) + sizeof(float) + sizeof(uint);


	//Channels size 
	std::map<std::string,BoneInfo>::const_iterator it;
	for (it = animation->bones.begin(); it != animation->bones.end(); ++it)
		size += AnimationLoader::GetChannelsSize(it->second);



	return uint();
}
