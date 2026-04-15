#include "MenuScene.h"
#include "GameManager.h"

void MenuScene::Start()
{

}

void MenuScene::Update()
{
	bool exitScene = false;

	while (!exitScene)
	{
		Sleep(100);
		//GameManager::GetInstance().PrintHi();
		/*for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update();
		}*/

		
		exitScene = ChooseScene();

		Render();
	}
}

bool MenuScene::ChooseScene()
{
	bool exitScene = false;

	if (GetAsyncKeyState('1'))
	{
		nextScene = SceneIndex::GAMEPLAY;
		exitScene = true;
	}
	else if (GetAsyncKeyState('2'))
	{
		nextScene = SceneIndex::RANKING;
		exitScene = true;
	}
	else if (GetAsyncKeyState('3'))
	{
		nextScene = SceneIndex::EXIT;
		exitScene = true;
	}
	
	return exitScene;
}

void MenuScene::Render()
{
	system("cls");
	std::cout << "===== Welcome to BreakOut =====\n\n - Press 1 to start game\n - Press 2 to show the ranking\n - Press 3 to load game\n - Press 4 to exit";
}

void MenuScene::Clear()
{

}