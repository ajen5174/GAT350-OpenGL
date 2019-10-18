#include "input.h"

bool Input::Initialize()
{
	m_keyboard_state = SDL_GetKeyboardState(NULL);

	return true;
}

void Input::Shutdown()
{
}

void Input::Update()
{
}

bool Input::GetKey(SDL_Scancode scancode)
{
	return m_keyboard_state[scancode];
}
