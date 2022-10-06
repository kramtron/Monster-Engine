#include "R_Mesh.h"

M_Mesh::M_Mesh()
{
}

M_Mesh::~M_Mesh()
{
	delete[num_vertices] vertices;
	delete[num_indices] indices;
}

void M_Mesh::meshRenderer()
{


	glBegin(GL_TRIANGLES);

	//Check every indice
	for (int i = 0; i < num_indices; i++) {
		//For every indice, grab 3 floats, xyz
		glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
	}

	glEnd();
	
}


