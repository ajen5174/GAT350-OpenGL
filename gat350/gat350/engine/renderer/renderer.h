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

private:
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_context;

};
