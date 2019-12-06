#include "renderer.h"

bool Renderer::Initialize()
{
	return Initialize(1280, 720, false);
}

bool Renderer::Initialize(u32 width, u32 height, bool fullscreen)
{
	m_width = width;
	m_height = height;

	Uint32 flags = SDL_WINDOW_OPENGL;
	flags |= (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

	m_window = SDL_CreateWindow("OpenGL", 100, 100, width, height, flags);
	if (m_window == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetSwapInterval(1);

	m_context = SDL_GL_CreateContext(m_window);
	if (!gladLoadGL()) {
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);


	return false;
}

void Renderer::Shutdown()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);

}

void Renderer::Update()
{
}

void Renderer::ClearBuffer()
{
	glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}
