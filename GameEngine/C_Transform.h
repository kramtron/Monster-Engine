#pragma once
#include "MathGeoLib.h"


class C_Transform
{

public:
	
	C_Transform();
	~C_Transform();



public:



	/*float4x4 localTransform;
	float4x4 globalTransform;*/


	float3 position;
	float3 scale;
	Quat rotation;



};

