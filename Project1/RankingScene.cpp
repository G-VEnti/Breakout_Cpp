#include "RankingScene.h"
#include "FileManager.h"
#include <string>
#include <fstream>



void RankingScene::Start()
{
	rankedPlayers = FileManager::ReadRanking();
	ranking = FileManager::RankingToString(rankedPlayers);
}

void RankingScene::Update()
{
	bool exitScene = false;

	while (!exitScene)
	{
		Sleep(100);
		//GameManager::GetInstance().PrintHi();
		/*for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update();
		}*/


		exitScene = GetAsyncKeyState('2');

		Render();
	}

	nextScene = SceneIndex::MAIN_MENU;
}


void RankingScene::Render()
{
	system("cls");
	std::cout << "_____Ranking_____\n\n" << ranking << std::endl;
	std::cout << "Press 2 to return to the main menu.";
}

void RankingScene::Clear()
{

}