#include "editor.h"
#include "../engine.h"
#include "../input/input.h"
#include "../framework/actor.h"

bool Editor::Initialize()
{
	m_engine->Get<Input>()->AddAction("visible", SDL_SCANCODE_GRAVE, Input::KEYBOARD);
	return true;
}

void Editor::Shutdown()
{
}

void Editor::Update()
{
	if (m_engine->Get<Input>()->GetButton("visible", Input::eButtonState::PRESSED)) m_visible = !m_visible;
}

void Editor::UpdateGUI()
{
	if (!m_visible) return;

	if (!ImGui::CollapsingHeader("Scene")) return;

	std::vector<Actor*> actors = m_scene->Get<Actor>();

	for (Actor* actor : actors)
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		if (ImGui::TreeNodeEx(actor, node_flags, actor->m_name.c_str()))
			if (ImGui::IsItemClicked())
				m_actor = actor;
	}

	if (!ImGui::CollapsingHeader("Scene")) return;

	if (m_actor)
	{
		m_actor->Edit();

	}
}
