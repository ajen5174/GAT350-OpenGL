#pragma once
#include "../engine/framework/scene.h"

class CubemapScene : public Scene
{
public:
	OBJECT_DECLARATION(CubemapScene, Scene)

	bool Create(const Name& name) override;
	void Update() override;
	void Draw() override;

public:
	//set up uniforms for these
	float m_index = 2.0f;
	float m_mix = 0.5f;

};