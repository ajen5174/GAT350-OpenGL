#include "scene.h"

void Scene::Update()
{
	for (const auto& actor : m_actors)
	{
		if(actor->m_active) actor->Update();
	}
}

void Scene::Draw()
{
	for (const auto& actor : m_actors)
	{
		if(actor->m_active) actor->Draw();
	}
}
