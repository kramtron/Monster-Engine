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

void M_Mesh::meshRenderer(const float* globalT, TextureTypes textureT)
{

	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);

	switch (textureT) {
	case TextureTypes::CURRENT:
		glBindTexture(GL_TEXTURE_2D, textureID);
		break;
	case TextureTypes::CHECKERS:
		glBindTexture(GL_TEXTURE_2D, TextureLoader::LoadTexture("Assets/Baker_house.png"));
		break;
	default:
		glBindTexture(GL_TEXTURE_2D, 0);
		break;
	}

	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);


	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * 3, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_indices, indices, GL_STATIC_DRAW);

	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARG, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARG, (void*)(3 * sizeof(float)));


	glPushMatrix();
	glMultMatrixf(globalT);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);


	glPopMatrix(); // Unbind transform matrix


	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);*/

	

	// Unbind buffers
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
}


