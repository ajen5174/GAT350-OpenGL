#pragma once
#include "../framework/system.h"

class Input : public System
{
public:
	enum eButtonState
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

	enum eDevice
	{
		KEYBOARD,
		MOUSE,
		CONTROLLER
	};

	enum eAxis
	{
		X,
		Y,
		Z
	};

	struct InputInfo
	{
		int id;
		eDevice device;
		int index;
	};

	struct ControllerInfo
	{
		SDL_GameController* controller;

		Uint8 button_state[SDL_CONTROLLER_BUTTON_MAX];
		Uint8 prev_button_state[SDL_CONTROLLER_BUTTON_MAX];
		float axis[SDL_CONTROLLER_AXIS_MAX];
		float prev_axis[SDL_CONTROLLER_AXIS_MAX];
	};

public:
	OBJECT_DECLARATION(Input, System)

	bool Initialize();
	void Shutdown();
	void Update();

	void AddAction(const Name& action, int id, eDevice device = KEYBOARD, int index = 0);
	
	eButtonState GetButton(const Name& action);
	bool GetButton(const Name& action, eButtonState state);
	float GetAxisAbsolute(const Name& action);
	float GetAxisRelative(const Name& action);

	eButtonState GetButtonState(int button, eDevice device = eDevice::KEYBOARD, int index = 0);
	float GetAxisAbsolute(eAxis axis, eDevice device = eDevice::MOUSE, size_t index = 0);
	float GetAxisRelative(eAxis axis, eDevice device = eDevice::MOUSE, size_t index = 0);

	void SetMouseRelative(bool enable = true);

protected:
	bool GetButtonDown(int button, eDevice device, int index = 0);
	bool GetPreviousButtonDown(int button, eDevice device, int index = 0);

private:
	// keyboard
	std::vector<Uint8> m_keystate;
	std::vector<Uint8> m_prev_keystate;
	int m_num_keys;

	// mouse
	Uint32 m_mouse_buttonstate;
	Uint32 m_prev_mouse_buttonstate;
	glm::vec2 m_mouse_position;
	glm::vec2 m_prev_mouse_position;
	glm::vec2 m_mouse_relative;
	bool m_mouse_relative_switch;

	// controller
	std::vector<ControllerInfo> m_controllers;

	// actions
	std::map<Name, InputInfo> m_actions;
};
