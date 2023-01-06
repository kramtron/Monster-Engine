#pragma once



#include "Globals.h"
#include "MathGeoLib.h"


#include "cimport.h"
#include "scene.h"
#include "postprocess.h"


#include  <vector>
#include <string>
#include <map>


typedef unsigned int uint;

struct BoneInfo {

	std::string name;

	//Time & Value
	std::map<double, float3> positionKeys;
	std::map<double, Quat> rotationKeys;
	std::map<double, float3> scaleKeys;

	//bool HasPosKey() const;
	std::map<double, float3>::const_iterator GetPrevPosKey(double currentKey) const;
	std::map<double, float3>::const_iterator GetNextPosKey(double currentKey) const;

	//bool HasRotKey() const;
	std::map<double, Quat>::const_iterator GetPrevRotKey(double currentKey) const;
	std::map<double, Quat>::const_iterator GetNextRotKey(double currentKey) const;

	//bool HasScaleKey() const;
	std::map<double, float3>::const_iterator GetPrevScaleKey(double currentKey) const;
	std::map<double, float3>::const_iterator GetNextScaleKey(double currentKey) const;

};

class T_AnimationLoader
{
public:
	T_AnimationLoader();
	~T_AnimationLoader();


	T_AnimationLoader* LoadAnimation(aiAnimation* importedAnimation);

	uint SaveCustomFormat(T_AnimationLoader* animation, char** buffer);
	uint GetBonesSize(const BoneInfo& channel);
	void SaveBones(const BoneInfo& channel, char** cursor);
	void SaveBoneKey(const std::map<double, float3>& map, char** cursor);
	void SaveBoneKey(const std::map<double, Quat>& map, char** cursor);

	std::string animationName;
	float duration;
	float ticksPerSecond;
	bool loopable = true;
	unsigned int numChannels;
	unsigned int initTimeAnim = 0;

	std::map<std::string, BoneInfo> bones;


};

