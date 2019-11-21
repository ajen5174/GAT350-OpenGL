#pragma once
#include "../engine/framework/scene.h"

class FXScene : public Scene
{
public:
	OBJECT_DECLARATION(FXScene, Scene)

	bool Create(const Name& name) override;
	void Update() override;
	void Draw() override;

public:
	glm::vec3 m_scale = glm::vec3(1);

	float m_time = 0.0f;
	float m_amplitude = 0.0f;
	float m_frequency = 0.0f;
	float m_rate = 1.0f;

	float m_dissolve = 0.0f;
	glm::vec3 m_discard_color = glm::vec3(0);

	glm::vec2 m_uv_scale = glm::vec2(1);
	glm::vec2 m_uv_offset = glm::vec2(0);
};