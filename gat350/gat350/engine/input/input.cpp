#include "input.h"

bool Input::Initialize()
{
	// create keyboard state buffers
	SDL_GetKeyboardState(&m_num_keys);
	m_keystate.resize(m_num_keys);
	m_prev_keystate.resize(m_num_keys);

	// set initial keyboard states
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate.data(), keystate, m_num_keys);
	memcpy(m_prev_keystate.data(), m_keystate.data(), m_num_keys);

	// set initial mouse buttons states
	SDL_Point axis;
	m_mouse_buttonstate = SDL_GetMouseState(&axis.x, &axis.y);
	m_prev_mouse_buttonstate = m_mouse_buttonstate;
	m_mouse_position = glm::vec2(axis.x, axis.y);
	m_prev_mouse_position = m_mouse_position;
	
	// query controllers attached, add controller info to controllers
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			ControllerInfo controllerInfo;
			controllerInfo.controller = SDL_GameControllerOpen(i);
			memset(controllerInfo.button_state, 0, SDL_CONTROLLER_BUTTON_MAX);
			memset(controllerInfo.prev_button_state, 0, SDL_CONTROLLER_BUTTON_MAX);
			memset(controllerInfo.axis, 0, SDL_CONTROLLER_AXIS_MAX);
			memset(controllerInfo.prev_axis, 0, SDL_CONTROLLER_AXIS_MAX);

			m_controllers.push_back(controllerInfo);
		}
	}

	return true;
}

void Input::Shutdown()
{
	//
}

void Input::Update()
{
	// set previous keyboard state
	memcpy(m_prev_keystate.data(), m_keystate.data(), m_num_keys);
	// get current keyboard state
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate.data(), keystate, m_num_keys);

	// set previous mouse state
	m_prev_mouse_buttonstate = m_mouse_buttonstate;
	m_prev_mouse_position = m_mouse_position;
	// get current mouse state
	SDL_Point axis;
	m_mouse_buttonstate = SDL_GetMouseState(&axis.x, &axis.y);
	m_mouse_position = glm::vec2(axis.x, axis.y);
	// get relative mouse state
	if (SDL_GetRelativeMouseMode())
	{
		m_mouse_buttonstate = SDL_GetRelativeMouseState(&axis.x, &axis.y);
		m_mouse_relative = (m_mouse_relative_switch) ? glm::vec2(0, 0) : glm::vec2(axis.x, axis.y);
		m_mouse_relative_switch = false;
	}

	// update controllers
	for (ControllerInfo& controllerInfo : m_controllers)
	{
		// controller buttons
		memcpy(controllerInfo.prev_button_state, controllerInfo.button_state, SDL_CONTROLLER_BUTTON_MAX);
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
		{
			controllerInfo.button_state[i] = SDL_GameControllerGetButton(controllerInfo.controller, (SDL_GameControllerButton)i);
		}

		// controller axis
		memcpy(controllerInfo.prev_axis, controllerInfo.axis, SDL_CONTROLLER_AXIS_MAX);
		for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++)
		{
			Sint16 value = SDL_GameControllerGetAxis(controllerInfo.controller, (SDL_GameControllerAxis)i);
			controllerInfo.axis[i] = value / float(SDL_MAX_SINT16);
		}
	}
}

void Input::AddAction(const Name& action, int id, eDevice device, int index)
{
	auto iter = m_actions.find(action);
	ASSERT(iter == m_actions.end());

	if (iter == m_actions.end())
	{
		InputInfo inputInfo = { id, device, index };
		m_actions[action] = inputInfo;
	}
}

Input::eButtonState Input::GetButton(const Name& action)
{
	eButtonState state = eButtonState::IDLE;

	auto iter = m_actions.find(action);
	if (iter != m_actions.end())
	{
		InputInfo inputInfo = iter->second;
		state = GetButtonState(inputInfo.id, inputInfo.device, inputInfo.index);
	}

	return state;
}

bool Input::GetButton(const Name& action, eButtonState state)
{
	return GetButton(action) == state;
}

float Input::GetAxisAbsolute(const Name& action)
{
	float axis = 0.0f;

	auto iter = m_actions.find(action);
	if (iter != m_actions.end())
	{
		InputInfo inputInfo = iter->second;
		axis = GetAxisAbsolute(static_cast<eAxis>(inputInfo.id), inputInfo.device, inputInfo.index);
	}

	return axis;
}

float Input::GetAxisRelative(const Name& action)
{
	float axis = 0.0f;

	auto iter = m_actions.find(action);
	if (iter != m_actions.end())
	{
		InputInfo inputInfo = iter->second;
		axis = GetAxisRelative(static_cast<eAxis>(inputInfo.id), inputInfo.device, inputInfo.index);
	}

	return axis;
}

Input::eButtonState Input::GetButtonState(int button, eDevice device, int index)
{
	eButtonState state = eButtonState::IDLE;

	bool button_down = GetButtonDown(button, device, index);
	bool prev_button_down = GetPreviousButtonDown(button, device, index);

	if (button_down)
	{
		state = (prev_button_down) ? eButtonState::HELD : eButtonState::PRESSED;
	}
	else
	{
		state = (prev_button_down) ? eButtonState::RELEASED : eButtonState::IDLE;
	}

	return state;
}

float Input::GetAxisAbsolute(eAxis axis, eDevice device, size_t index)
{
	float axis_value = 0.0f;

	switch (device)
	{
	case eDevice::KEYBOARD:
		ASSERT_MSG(0, "Keyboard does not support axis.");
		break;

	case eDevice::MOUSE:
		axis_value = m_mouse_position[axis];
		break;

	case eDevice::CONTROLLER:
		ASSERT_MSG(index < m_controllers.size(), "Invalid controller index.");
		axis_value = m_controllers[index].axis[axis];
		break;
	}

	return axis_value;
}

float Input::GetAxisRelative(eAxis axis, eDevice device, size_t index)
{
	float axis_value = 0.0f;

	switch (device)
	{
	case eDevice::KEYBOARD:
		ASSERT_MSG(0, "Keyboard does not support axis.");
		break;

	case eDevice::MOUSE:
		axis_value = (SDL_GetRelativeMouseMode()) ? m_mouse_relative[axis] : m_mouse_position[axis] - m_prev_mouse_position[axis];
		break;

	case eDevice::CONTROLLER:
		ASSERT_MSG(index < m_controllers.size(), "Invalid controller index.");
		axis_value = m_controllers[index].axis[axis] - m_controllers[index].prev_axis[axis];
		break;
	}

	return axis_value;
}

void Input::SetMouseRelative(bool enable)
{
	SDL_SetRelativeMouseMode(enable ? SDL_TRUE : SDL_FALSE);
	m_mouse_relative_switch = true;
}

bool Input::GetButtonDown(int button, eDevice device, int index)
{
	bool button_down = false;

	switch (device)
	{
	case eDevice::KEYBOARD:
		button_down = m_keystate[button];
		break;

	case eDevice::MOUSE:
		button_down = m_mouse_buttonstate & SDL_BUTTON(button);
		break;

	case eDevice::CONTROLLER:
		ASSERT_MSG(index < m_controllers.size(), "Invalid controller index.");
		button_down = m_controllers[index].button_state[button];
		break;
	}

	return button_down;
}

bool Input::GetPreviousButtonDown(int button, eDevice device, int index)
{
	bool button_down = false;

	switch (device)
	{
	case eDevice::KEYBOARD:
		button_down = m_prev_keystate[button];
		break;

	case eDevice::MOUSE:
		button_down = m_prev_mouse_buttonstate & SDL_BUTTON(button);
		break;

	case eDevice::CONTROLLER:
		assert(index < m_controllers.size());
		button_down = m_controllers[index].prev_button_state[button];
		break;
	}

	return button_down;
}
