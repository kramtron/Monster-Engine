
#include "Globals.h"

#include "Primitive.h"

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImHierarchyWindow.h"

// ------------------------------------------------------------
Primitive::Primitive() : transform(IdentityMatrix), color(White), wire(false), axis(false), type(PrimitiveTypes::Primitive_Point)
{}

// ------------------------------------------------------------
PrimitiveTypes Primitive::GetType() const
{
	return type;
}


void Primitive::CreatePrimitive(GameObject* p=nullptr, PrimitiveType t = PrimitiveType::EMPTY)
{
	
	if (p == nullptr) {

		ImHierarchyWindow* ImH = new ImHierarchyWindow;

		p = ImH->rootGameObject;
	}

	switch (t)
	{
	case PrimitiveType::CUBE:
	{

		GameObject* cube = new GameObject("Cube", p, "cube", MeshLoader::LoadFile("Assets/cube.fbx"));
		break;

	}
	case PrimitiveType::PLANE:
	{
		GameObject* cube2 = new GameObject("Plane", p, "plane", MeshLoader::LoadFile("Assets/plane.fbx"));

		break;
	}
	case PrimitiveType::SPHERE:
	{
		GameObject* cube3 = new GameObject("Sphere", p, "sphere", MeshLoader::LoadFile("Assets/sphere.fbx"));

		break;
	}
	case PrimitiveType::CYLINDER:
	{
		GameObject* cube4 = new GameObject("Cylinder", p, "cylinder", MeshLoader::LoadFile("Assets/cylinder.fbx"));

		break;
	}
	case PrimitiveType::EMPTY:
	{
		GameObject* cube4 = new GameObject("Empty", p, "cylinder",nullptr);

		break;
	}
	}


}

// ------------------------------------------------------------
void Primitive::Render() const
{

	glPushMatrix();
	glMultMatrixf(transform.M);

	if(axis == true)
	{
		// Draw Axis Grid
		glLineWidth(2.0f);

		glBegin(GL_LINES);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
		glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
		glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
		glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

		glEnd();

		glLineWidth(1.0f);
	}

	glColor3f(color.r, color.g, color.b);

	if(wire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	InnerRender();

	glPopMatrix();
}

// ------------------------------------------------------------
void Primitive::InnerRender() const
{
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glPointSize(1.0f);
}

// ------------------------------------------------------------
void Primitive::SetPos(float x, float y, float z)
{
	transform.translate(x, y, z);
}

// ------------------------------------------------------------
void Primitive::SetRotation(float angle, const vec3 &u)
{
	transform.rotate(angle, u);
}

// ------------------------------------------------------------
void Primitive::Scale(float x, float y, float z)
{
	transform.scale(x, y, z);
}

// CUBE ============================================


// SPHERE ============================================



// CYLINDER ============================================




// LINE ==================================================
