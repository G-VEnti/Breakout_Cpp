#include "CreditsScene.h"

void CreditsScene::Start()
{
}

void CreditsScene::Update()
{
	bool exitScene = false;

	while (!exitScene)
	{
		Sleep(100);
		exitScene = GetAsyncKeyState('3');
		Render();
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	nextScene = SceneIndex::MAIN_MENU;
}

void CreditsScene::Render()
{
	system("cls");
	std::cout << "^^^^^Credits^^^^^\n\n\n Game made by:\n\n - Isaac Winecastle\n - Gerard Hardgreen\n\n\n Thank you for playing/correcting our game Marti Theblacksmith :)\n\n Press 3 to retur to the menu";
}

void CreditsScene::Clear()
{

}
