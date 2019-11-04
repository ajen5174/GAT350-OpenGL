#include "gui.h"
#include "renderer.h"

#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace GUI
{
	bool Initialize(Renderer* renderer)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui_ImplSDL2_InitForOpenGL(renderer->GetWindow(), renderer->GetContext());
		const char* glsl_version = "#version 430";
		ImGui_ImplOpenGL3_Init(glsl_version);

		ImGui::StyleColorsDark();

		return true;
	}

	void Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void Update(SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	void Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Begin(Renderer* renderer)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(renderer->GetWindow());
		ImGui::NewFrame();
	}

	void End()
	{
		ImGui::EndFrame();
	}
}
