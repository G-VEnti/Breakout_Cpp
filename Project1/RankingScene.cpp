#include "RankingScene.h"
#include <fstream>
#include <string>

void RankingScene::Start()
{
	ranking = ReadBin();
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

std::string RankingScene::ReadBin()
{
#pragma region dataInsertTest


	/*std::fstream saveBinFile;
	PlayerStats actualPlayer;
	int playerNum;

	saveBinFile.open("Ranking.bin", std::ios::out | std::ios::binary);

	if (!saveBinFile.is_open())
	{
		std::cout << "[ERROR] Can't open the file.";
	}
	else
	{
		std::cin >> playerNum;
		saveBinFile.write(reinterpret_cast<char*>(&playerNum), sizeof(int));
		for (int i = 0; i < playerNum; i++)
		{
			std::cout << "Enter username: ";
			std::cin >> actualPlayer.playerName;
			std::cout << "Enter score: ";
			std::cin >> actualPlayer.score;

			size_t usernameStrSize = actualPlayer.playerName.size();

			saveBinFile.write(reinterpret_cast<char*>(&usernameStrSize), sizeof(usernameStrSize));
			saveBinFile.write(actualPlayer.playerName.c_str(), sizeof(char) * usernameStrSize);
			saveBinFile.write(reinterpret_cast<char*>(&actualPlayer.score), sizeof(int));
		}
	}
	saveBinFile.close();*/
#pragma endregion

	std::ifstream saveBinFile;
	PlayerStats player;
	int rankedPlayers;
	size_t nameSize;
	std::string ranking = "";

	saveBinFile.open("Ranking.bin", std::ios::in | std::ios::binary);
	if (!saveBinFile.is_open()) std::cout << "[ERROR] Can't open ranking file.";
	else
	{
		saveBinFile.read(reinterpret_cast<char*>(&rankedPlayers), sizeof(int));
		for (int i = 0; i < rankedPlayers; i++)
		{
			saveBinFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
			player.playerName.resize(nameSize);
			saveBinFile.read(&player.playerName[0], sizeof(char) * nameSize);
			saveBinFile.read(reinterpret_cast<char*>(&player.score), sizeof(int));
			ranking += std::to_string(i + 1) + ". " + player.playerName + " Score = " + std::to_string(player.score) + ".\n";
		}
	}
	saveBinFile.close();
	return ranking;
}

void RankingScene::Clear()
{

}