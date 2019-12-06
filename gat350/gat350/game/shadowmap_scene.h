#pragma once
#include "../engine/framework/scene.h"

class ShadowmapScene : public Scene
{
public:
	OBJECT_DECLARATION(ShadowmapScene, Scene)

	bool Create(const Name& name) override;
	void Update() override;
	void Draw() override;

protected:
	void RenderToTexture();
	void RenderScene();

};