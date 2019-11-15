#pragma once

#include "def.h"
#include "framework/object.h"
#include "framework/scene.h"
#include "framework/system.h"

class Engine : public Object
{
public:
	OBJECT_DECLARATION(Engine, Object)
	virtual ~Engine() {}

	bool Initialize();
	void Shutdown();
	void Update();

	bool IsQuit() { return m_quit; }

	template <typename T>
	T* Get()
	{
		for (const auto& system : m_systems)
		{
			if (dynamic_cast<T*>(system.get()) != nullptr)
			{
				return static_cast<T*>(system.get());
			}
		}

		return nullptr;
	}

	object_factory_t* Factory() const { return m_factory.get(); }
	resource_manager_t* Resources() const { return m_resources.get(); }

	SDL_Event& GetEvent() { return m_event; }

protected:
	bool m_quit = false;
	SDL_Event m_event;

	std::vector<std::unique_ptr<class System>> m_systems;
	std::unique_ptr<object_factory_t> m_factory;
	std::unique_ptr<resource_manager_t> m_resources;
};
