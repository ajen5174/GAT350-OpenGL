#pragma once
#include "../framework/system.h"

class Editor : public System
{
public:
	OBJECT_DECLARATION(Editor, System)
	~Editor() {}

	bool Initialize();
	void Shutdown();
	void Update();

	void UpdateGUI();

public:
	bool m_visible = false;
	class Scene* m_scene = nullptr;
	class Actor* m_actor = nullptr;
};