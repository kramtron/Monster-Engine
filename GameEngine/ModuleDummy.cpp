#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "glew.h"

#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>


ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleDummy::~ModuleDummy()
{

}

bool ModuleDummy::Start()
{
	LOG("Testing");
	bool ret = true;

	
	return ret;
}

bool ModuleDummy::CleanUp()
{
	LOG("Cleaning test");

	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	//Todo lo puesto a constinuacion ns si va aquí o en update
		//Va aquí o en moduleRender?
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{
	static int counter = 0;

	ImGui::Begin("Tests");

	//GL_POSITION = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	if (ImGui::CollapsingHeader("Button", false))
	{
		//ImGui::Button("Count");
		if (ImGui::Button("Count"))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::ColorButton("ColBut", {1,0,0,1}))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::SmallButton("Small"))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Radio", true)) //the true or false its to light up the button
		{
			counter++;
		}

		ImGui::Text("counter = %d", counter);
	}

	if (ImGui::CollapsingHeader("Text", false))
	{
		ImGui::Text("Yes bby\n shit happens \"My Love\"");
		ImGui::SameLine();
		ImGui::TextColored(clear_color,"NOPPP");
		ImGui::BulletText("YASSS\n \"The Y\" for the frineds");
		ImGui::Separator();
		ImGui::TextWrapped("YEY");
		ImGui::Separator();
		ImGui::TextUnformatted("YEY");

	}

	if (ImGui::CollapsingHeader("Info", false))
		ImGui::ShowUserGuide();

	if (ImGui::CollapsingHeader("ColorChanger", false)) {
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		ImGui::TextColored(clear_color, "ColorTester");
	}
	if (ImGui::CollapsingHeader("windowsColorChanger", false)) {
		ImGui::ColorEdit3("clear color", (float*)&back_window_color); // Edit 3 floats representing a color
		//ImGui::SetNextWindowBgAlpha(0);
	}
	if (ImGui::CollapsingHeader("windowsColorChanger", false)) {
		ImGui::ShowMetricsWindow();
	}


	//ImGui::CollapsingHeader("HEY", false);

	//
	//ImGuiKey_All = Tab (for now)
	//
	if (ImGui::IsKeyReleased(ImGuiKey_All))
	{
		counter++;
	}
	
	//ImGui::PushID();

	ImGui::End();
	ImGui::Begin("Hardware");
	if (ImGui::CollapsingHeader("HardwareInfo", false)) {
		
	}
	ImGui::End();

	ImGui::BeginGroup();


	ImGui::EndGroup();

	return UPDATE_CONTINUE;

}

update_status ModuleDummy::PostUpdate(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	Cube c(1, 1, 1);
	c.Render();
	

	return UPDATE_CONTINUE;
}