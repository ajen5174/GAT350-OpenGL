#pragma once
#include "../framework/system.h"

class Renderer : public System
{
public:
	OBJECT_DECLARATION(Renderer, System)

	~Renderer() {}

	bool Initialize();
	bool Initialize(u32 width, u32 height, bool fullscreen = false);
	void Shutdown();
	void Update();
	
	void ClearBuffer();
	void SwapBuffer();

	SDL_Window* GetWindow() { return m_window; }
	SDL_GLContext GetContext() { return m_context; }

	
	void SetViewport(u32 x, u32 y, u32 width, u32 height) { glViewport(x, y, width, height); }
	void RestoreViewport() { glViewport(0, 0, m_width, m_height); }

	u32 GetWidth() { return m_width; }
	u32 GetHeight() { return m_height; }

private:
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_context;

	u32 m_width;
	u32 m_height;

};
