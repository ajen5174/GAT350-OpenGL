#pragma once
#include "../framework/actor.h"

class Camera : public Actor
{
public:
	OBJECT_DECLARATION(Camera, Actor)
	virtual ~Camera() {}
	
	virtual bool Create(const Name& name) override;
	virtual void Update() override;
	void SetProjection(float fov, float aspect_ratio, float near_clip, float far_clip);

public:
	glm::mat4 m_view_matrix;
	glm::mat4 m_projection_matrix;

	bool m_user_camera = true;
	float fov;
	float aspect_ratio;
	float near_clip;
	float far_clip;
};