#include "ImConfigWindow.h"


int ImConfigWindow::fpsLimit = 60;

vector<float> ImConfigWindow::fpsDebug;
vector<float> ImConfigWindow::fpsDebugAux = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
vector<float> ImConfigWindow::timeDebug;
vector<float> ImConfigWindow::timeDebugAux = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

bool ImConfigWindow::isFullScreen = false;
bool ImConfigWindow::isBor = false;
bool ImConfigWindow::isRe = true;

bool ImConfigWindow::vSync = false;
float ImConfigWindow::bright = 0;
bool ImConfigWindow::lights = false;
bool ImConfigWindow::depths = false;
bool ImConfigWindow::isCullFaces = false;
bool ImConfigWindow::colorM = false;
bool ImConfigWindow::text2D = false;
float ImConfigWindow::bright_aux = 0;


void ImConfigWindow::Update(Application* app, float dt)
{

	ImGui::Begin("Configuration", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);


	if (ImGui::CollapsingHeader("FPS"))
	{
		float fps = 1 / dt;
		float ms = dt * 1000.0f;

		fpsDebug.push_back(fps);
		timeDebug.push_back(ms);


		if (fpsDebug.size() >= 24)
		{
			fpsDebugAux[0] = fpsDebug[fpsDebug.size() - 1];
			timeDebugAux[0] = timeDebug[timeDebug.size() - 1];
		}

		ImGui::LabelText("Monster", "Engine Name:");
		ImGui::LabelText("UPC CITM", "Organisation:");

		ImGui::Text("\n");
		ImGui::Text("Min FPS");
		ImGui::SameLine();
		ImGui::SliderInt(" Max FPS", &fpsLimit, 1, 165);

		ImGui::Text("\n");

		char name[25];
		sprintf_s(name, 25, "FPS %1.f", fpsDebug[fpsDebug.size() - 1]);
		ImGui::PlotHistogram("##_FPS_", &fpsDebug[0], fpsDebugAux.size(), 0, name, 0.0f, 100.0f, ImVec2(400, 75));

		ImGui::Text("\n");

		sprintf_s(name, 25, "Milliseconds %0.f", timeDebug[timeDebug.size() - 1]);
		ImGui::PlotHistogram("##_MS_", &timeDebug[0], timeDebugAux.size(), 0, name, 0.0f, 100.0f, ImVec2(400, 75));

		for (int i = 0; i < fpsDebug.size() - 1; i++)
		{
			fpsDebug[i] = fpsDebug[i + 1];
			timeDebug[i] = timeDebug[i + 1];
		}

		LOG( "%d", fpsDebug.size(), ConsoleType::MSG);

		ImGui::Text("\n");



		if (isFullScreen)
		{
			ImGui::BulletText("Width: ");
			ImGui::SameLine();
			ImGui::TextColored({ 0,255,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->w);

			ImGui::BulletText("Height: ");
			ImGui::SameLine();
			ImGui::TextColored({ 0,255,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->h);
		}
		else
		{
			ImGui::BulletText("Width: ");
			ImGui::SameLine();
			ImGui::TextColored({ 255,0,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->w);

			ImGui::BulletText("Height: ");
			ImGui::SameLine();
			ImGui::TextColored({ 255,0,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->h);
		}
		ImGui::Text("\n");

	}



	ImGui::Separator();

	if (ImGui::CollapsingHeader("Visual"))
	{
		if (ImGui::Checkbox("Vsync", &vSync))
		{
			if (vSync)
			{
				SDL_GL_SetSwapInterval(1);
				LOGT(ConsoleType::SYSTEM, "Vsync On");
			}
			else
			{
				SDL_GL_SetSwapInterval(0);
				LOGT(ConsoleType::SYSTEM, "Vsync Off");
			}
		}

		

		if (ImGui::Checkbox("Lights", &lights))
		{
			if (lights)
			{
				glEnable(GL_LIGHTING);
				LOGT(ConsoleType::SYSTEM, "Lights On");
			}
			else
			{
				glDisable(GL_LIGHTING);
				LOGT(ConsoleType::SYSTEM, "Lights Off");
			}
		}

		if (ImGui::Checkbox("Depth Test", &depths))
		{
			if (depths)
			{
				glEnable(GL_DEPTH_TEST);
				LOGT(ConsoleType::SYSTEM, "Depth On");
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
				LOGT(ConsoleType::SYSTEM, "Depth Off");
			}
		}

		if (ImGui::Checkbox("Cull Face", &isCullFaces))
		{
			if (isCullFaces)
			{
				glEnable(GL_CULL_FACE);
				LOGT(ConsoleType::SYSTEM, "Cull_Face On");
			}
			else
			{
				glDisable(GL_CULL_FACE);
				LOGT(ConsoleType::SYSTEM, "Cull_Face Off");
			}
		}
		if (ImGui::Checkbox("Texture 2D", &text2D))
		{
			if (text2D)
			{
				glEnable(GL_TEXTURE_2D);
				LOGT(ConsoleType::SYSTEM, "Texture_2D On");
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
				LOGT(ConsoleType::SYSTEM, "Texture_2D Off");
			}
		}
		if (ImGui::Checkbox("Color Material", &colorM))
		{
			if (colorM)
			{
				glEnable(GL_COLOR_MATERIAL);
				LOGT(ConsoleType::SYSTEM, "Color_Material On");
			}
			else
			{
				glDisable(GL_COLOR_MATERIAL);
				LOGT(ConsoleType::SYSTEM, "Color_Material Off");
			}
		}

		
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::Text("\n");
		ImGui::Separator();
		ImGui::Text("\n");

		SDL_version version;
		SDL_GetVersion(&version);

		ImGui::BulletText("SDL Version:");
		ImGui::SameLine(140);
		ImGui::Text("%u.%u.%u", version.major, version.minor, version.patch);

		ImGui::BulletText("OpenGL Version:");
		ImGui::SameLine(140);
		ImGui::Text("%s", glGetString(GL_VERSION));

		ImGui::BulletText("Glew Version:");
		ImGui::SameLine(140);
		ImGui::Text("%s", glewGetString(GLEW_VERSION));

		ImGui::BulletText("DevIL Version:");
		ImGui::SameLine(140);
		ImGui::Text("%s", glewGetString(GLEW_VERSION)); //ilGetInteger(IL_VERSION_NUM) < IL_VERSION)

		ImGui::Text("\n");
		ImGui::Separator();
		ImGui::Text("\n");

		int SDL_GetCPUCount(void);
		int SDL_GetCPUCacheLineSize(void);

		ImGui::BulletText("CPUs:");
		ImGui::SameLine(137);
		ImGui::Text("%d", SDL_GetCPUCount());


		int SDL_GetSystemRAM(void);

		ImGui::BulletText("System RAM:");
		ImGui::SameLine(130);
		ImGui::Text("% dGb", SDL_GetSystemRAM() / 1000);

		ImGui::BulletText("Caps:");
		ImGui::SameLine();

		SDL_bool SDL_Has3DNow(void);
		SDL_bool SDL_HasAltiVec(void);
		SDL_bool SDL_HasAVX(void);
		SDL_bool SDL_HasAVX2(void);
		SDL_bool SDL_HasMMX(void);
		SDL_bool SDL_HasRDTSC(void);
		SDL_bool SDL_HasSSE(void);
		SDL_bool SDL_HasSSE2(void);
		SDL_bool SDL_HasSSE3(void);
		SDL_bool SDL_HasSSE41(void);
		SDL_bool SDL_HasSSE42(void);

		if (SDL_Has3DNow())
		{
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("3DNow!");
		}

		if (SDL_HasAltiVec())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("AltiVec");
		}

		if (SDL_HasAVX())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("AVX");
		}

		if (SDL_HasAVX2())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("AVX2");
		}

		if (SDL_HasMMX())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("MMX");
		}

		if (SDL_HasRDTSC())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("RDTSC");
		}

		if (SDL_HasSSE())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE");
		}

		if (SDL_HasSSE2())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE2");
		}

		if (SDL_HasSSE3())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE3");
		}

		if (SDL_HasSSE41())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE41");
		}

		if (SDL_HasSSE42())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE42");
		}
	}


	ImGui::End();


}
