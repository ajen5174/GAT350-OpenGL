#include "camera.h"
#include "../input/input.h"
#include "../engine.h"

bool Camera::Create(const Name& name)
{
	m_name = name;

	m_engine->Get<Input>()->AddAction("camera_x", Input::X, Input::MOUSE);
	m_engine->Get<Input>()->AddAction("camera_y", Input::Y, Input::MOUSE);
	m_engine->Get<Input>()->AddAction("camera_orbit", SDL_BUTTON_RIGHT, Input::MOUSE);

	m_engine->Get<Input>()->AddAction("camera_forward", SDL_SCANCODE_W, Input::KEYBOARD);
	m_engine->Get<Input>()->AddAction("camera_backward", SDL_SCANCODE_S, Input::KEYBOARD);
	m_engine->Get<Input>()->AddAction("camera_left", SDL_SCANCODE_A, Input::KEYBOARD);
	m_engine->Get<Input>()->AddAction("camera_right", SDL_SCANCODE_D, Input::KEYBOARD);
	m_engine->Get<Input>()->AddAction("camera_up", SDL_SCANCODE_E, Input::KEYBOARD);
	m_engine->Get<Input>()->AddAction("camera_down", SDL_SCANCODE_Q, Input::KEYBOARD);

	return true;
}

void Camera::Update()
{
	if (m_user_camera)
	{
		glm::vec3 rotation(0);
		if (m_engine->Get<Input>()->GetButton("camera_orbit", Input::HELD))
		{
			rotation.x = m_engine->Get<Input>()->GetAxisRelative("camera_x") * 0.001f;
			rotation.y = m_engine->Get<Input>()->GetAxisRelative("camera_y") * 0.001f;

		}

		glm::quat pitch = glm::angleAxis(rotation.y, glm::vec3(1, 0, 0));
		glm::quat yaw = glm::angleAxis(rotation.x, glm::vec3(0, 1, 0));
		m_transform.rotation = pitch * m_transform.rotation * yaw;

		glm::vec3 translation(0);

		if (m_engine->Get<Input>()->GetButton("camera_forward", Input::eButtonState::HELD)) translation.z += 1.0f;
		if (m_engine->Get<Input>()->GetButton("camera_backward", Input::eButtonState::HELD)) translation.z -= 1.0f;
		if (m_engine->Get<Input>()->GetButton("camera_left", Input::eButtonState::HELD)) translation.x += 1.0f;
		if (m_engine->Get<Input>()->GetButton("camera_right", Input::eButtonState::HELD)) translation.x -= 1.0f;
		if (m_engine->Get<Input>()->GetButton("camera_up", Input::eButtonState::HELD)) translation.y += 1.0f;
		if (m_engine->Get<Input>()->GetButton("camera_down", Input::eButtonState::HELD)) translation.y -= 1.0f;

		translation = translation * 5.0f * g_timer.dt();
		m_transform.translation = m_transform.translation + (m_transform.rotation * translation);

		glm::vec3 target = m_transform.translation + m_transform.rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		m_view_matrix = glm::lookAt(m_transform.translation, target, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	

	
}

void Camera::SetProjection(float fov, float aspect_ratio, float near_clip, float far_clip)
{
	this->fov = fov;
	this->aspect_ratio = aspect_ratio;
	this->near_clip = near_clip;
	this->far_clip = far_clip;

	m_projection_matrix = glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
}
