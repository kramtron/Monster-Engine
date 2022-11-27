#include "R_Mesh.h"
#include "C_Transform.h"
#include "T_TextureLoader.h"

M_Mesh::M_Mesh()
{
}

M_Mesh::~M_Mesh()
{
	delete[] vertices;
	delete[] indices;
}

void M_Mesh::InitAABB()
{
	for (size_t i = 0; i < num_vertices * VERTEX_ARGUMENTS; i += VERTEX_ARGUMENTS) {
		tempVert.emplace_back(vertices[i], vertices[i + 1], vertices[i + 2]);
	}
	AABB_.SetFrom(&tempVert[0], tempVert.size());

}

void M_Mesh::meshRenderer(float4x4 globalT, TextureTypes textureT)
{

	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D, textureID);
 

	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);


	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARG, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARG, (void*)(3 * sizeof(float)));


	glPushMatrix();
	glMultMatrixf(globalT.ptr());

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);


	glPopMatrix(); // Unbind transform matrix


	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);*/

	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);


	OBB_ = AABB_;
	OBB_.Transform(globalT);
	global_AABB.SetNegativeInfinity();
	global_AABB.Enclose(OBB_);
}



void M_Mesh::RenderAABB() 
{

	OBB_.GetCornerPoints(tempCorn1);
	DrawAABB_Boxes(tempCorn1, float3(0, 255, 0));

	global_AABB.GetCornerPoints(tempCorn2);
	DrawAABB_Boxes(tempCorn2, float3(0, 255, 0));


}

void M_Mesh::DrawAABB_Boxes(float3* tempCorn, float3 color)
{

	int indices[24] = { 0,2,2,6,6,4,4,0,0,1,1,3,3,2,4,5,6,7,5,7,3,7,1,5 };

	glBegin(GL_LINES);
	glColor3fv(color.ptr());

	for (size_t i = 0; i < 24; i++)
	{
		glVertex3fv(tempCorn[indices[i]].ptr());
	}

	glColor3f(255.f, 255.f, 255.f);
	glEnd();

}


