#pragma once



typedef unsigned int uint;

class M_Mesh 
{

public:

	M_Mesh();
	~M_Mesh();



public:

	uint indices_count = 0;
	uint* indices = nullptr;

	uint num_vertices = 0;
	float* vertices = nullptr;


};
