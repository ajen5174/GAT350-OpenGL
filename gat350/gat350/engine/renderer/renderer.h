#pragma once
#include "../engine.h"

class Renderer
{
public:
	Renderer() {}
	~Renderer() {}

	bool Initialize(u32 width, u32 height, bool fullscreen = false);
	void Shutdown();
	
	void ClearBuffer();
	void SwapBuffer();

	SDL_Window* GetWindow() { return m_window; }
	SDL_GLContext GetContext() { return m_context; }

private:
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_context;

};
