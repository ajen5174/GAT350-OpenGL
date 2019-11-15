#include "scene.h"

void Scene::Update()
{
	for (const auto& actor : m_actors)
	{
		actor->Update();
	}
}

void Scene::Draw()
{
	for (const auto& actor : m_actors)
	{
		actor->Draw();
	}
}
