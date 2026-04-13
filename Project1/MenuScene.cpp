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

		exitScene = GetAsyncKeyState('1');

		Render();
	}

	nextScene = SceneIndex::GAMEPLAY;
}

void MenuScene::Render()
{
	system("cls");
	std::cout << "==== Welcome to BreakOut ====\n\n - Press 1 to start game\n - Press 2 to show the ranking\n - Press 3 to load game\n - Press 4 to exit";
}

void MenuScene::Clear()
{

}