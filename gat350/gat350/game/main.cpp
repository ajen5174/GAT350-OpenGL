#include "game_scene.h"
#include "../engine/engine.h"

int main(int argc, char** argv)
{
	std::shared_ptr<Engine> engine = std::make_shared<Engine>();
	engine->Initialize();

	std::unique_ptr<Scene> scene = std::make_unique<GameScene>(GameScene::GetClassName(), engine.get());
	scene->Create("scene");

	while (!engine->IsQuit())
	{
		engine->Update();

		scene->Update();
		scene->Draw();
	}
	engine->Shutdown();
	
	return 0;
}
