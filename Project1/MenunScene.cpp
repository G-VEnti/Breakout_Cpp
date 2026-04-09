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
		GameManager::GetInstance()->PrintHi();
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update();
		}

		exitScene = GetAsyncKeyState('1');

		Render();
	}

	nextScene = SceneIndex::GAMEPLAY;
}

void MenuScene::Render()
{
	system("cls");
	std::cout << "Menu, press 1 to continue:";
}

void MenuScene::Clear()
{

}