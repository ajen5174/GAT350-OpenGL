#pragma once
#include "../engine.h"

class Renderer;

namespace GUI
{
	bool Initialize(Renderer* renderer);
	void Shutdown();

	void Begin(Renderer* renderer);
	void End();
	void Update(SDL_Event& event);
	void Draw();
};