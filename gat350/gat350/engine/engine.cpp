#include "engine.h"
#include "input/input.h"
#include "renderer/renderer.h"
#include "renderer/program.h"
#include "renderer/vertex_index_array.h"
#include "renderer/texture.h"
#include "renderer/material.h"
#include "renderer/light.h"
#include "renderer/mesh.h"
#include "renderer/model.h"
#include "renderer/gui.h"
#include "renderer/camera.h"

bool Engine::Initialize()
{
	// core
	filesystem::set_current_path("content");
	Name::AllocNames();

	int result = SDL_Init(SDL_INIT_VIDEO);
	if (result != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// systems
	std::unique_ptr<Input> input = std::make_unique<Input>(Input::GetClassName(), this);
	input->Initialize();
	m_systems.push_back(std::move(input));

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(Renderer::GetClassName(), this);
	renderer->Initialize(1280, 720);
	m_systems.push_back(std::move(renderer));

	GUI::Initialize(Get<Renderer>());

	// factory
	m_factory = std::make_unique<object_factory_t>();
	m_factory->Register(Texture::GetClassName(), new Creator<Texture, Object>());
	m_factory->Register(Model::GetClassName(), new Creator<Model, Object>());
	m_factory->Register(Program::GetClassName(), new Creator<Program, Object>());
	m_factory->Register(Material::GetClassName(), new Creator<Material, Object>());
	m_factory->Register(Camera::GetClassName(), new Creator<Camera, Object>());
	m_factory->Register(Light::GetClassName(), new Creator<Light, Object>());

	// resources
	m_resources = std::make_unique<resource_manager_t>();

	return true;
}

void Engine::Shutdown()
{
	GUI::Shutdown();
	for (const std::unique_ptr<System>& system : m_systems)
	{
		system->Shutdown();
	}

	SDL_Quit();
	Name::FreeNames();
}

void Engine::Update()
{
	SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
	case SDL_QUIT:
		m_quit = true;
		break;
	case SDL_KEYDOWN:
		if (m_event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_quit = true;
		}
	}
	SDL_PumpEvents();

	g_timer.tick();
	for (const std::unique_ptr<System>& system : m_systems)
	{
		system->Update();
	}
}
