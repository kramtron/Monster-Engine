#pragma once


#include "MathGeoLib.h"



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
	T_AnimationLoader();
	



	uint SaveCustomFormat(T_AnimationLoader* animation, char** buffer);

	std::string animationName;
	float duration;
	float ticksPerSecond;
	bool loopable = true;
	unsigned int numChannels;
	unsigned int initTimeAnim = 0;

	std::map<std::string, BoneInfo> bones;


};

