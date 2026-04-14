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
	std::string userName;
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
			std::cin >> userName;

			size_t usernameStrSize = userName.size();

			saveBinFile.write(reinterpret_cast<char*>(&usernameStrSize), sizeof(usernameStrSize));
			saveBinFile.write(userName.c_str(), sizeof(char) * usernameStrSize);

		}
	}
	saveBinFile.close();*/
#pragma endregion

	std::ifstream saveBinFile;
	std::string playerName;
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
			playerName.resize(nameSize);
			saveBinFile.read(&playerName[0], sizeof(char) * nameSize);
			ranking += std::to_string(i + 1) + ". " + playerName + ".\n";
		}
	}
	saveBinFile.close();
	return ranking;
}

void RankingScene::Clear()
{

}