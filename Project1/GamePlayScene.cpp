#include "GamePlayScene.h"
#include "Const.h"
#include "Wall.h" 
#include "Pad.h"
#include "Brick.h"
#include "Ball.h"
#include "Vector2.h"
#include "GameManager.h"
#include "Scene.h"
#include "Const.h"
#include <string>
#include <list>
#include <fstream>

void GameplayScene::CreateWalls(std::vector<GameObject*>& objects) {
	for (int i = 0; i < MAP_SIZE; i++) {
		objects.push_back(new Wall(Vector2(i, 0), YELLOW, false));
		objects.push_back(new Wall(Vector2(i, MAP_SIZE - 1), YELLOW, true));

		if (i > 0 && i < MAP_SIZE - 1) {
			objects.push_back(new Wall(Vector2(0, i), YELLOW, false));
			objects.push_back(new Wall(Vector2(MAP_SIZE - 1, i), YELLOW, false));
		}
	}
}

void GameplayScene::CreateBricks(std::vector<GameObject*>& objects) {
	for (int row = 1; row <= 3; row++) {
		for (int col = 1; col < MAP_SIZE - 1; col++) {
			objects.push_back(new Brick(Vector2(col, row), CYAN));
		}
	}
}

void GameplayScene::CreatePlayer(std::vector<GameObject*>& objects) {
	objects.push_back(new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 1, MAP_SIZE));
}

void GameplayScene::CreateBall(std::vector<GameObject*>& objects) {
	objects.push_back(new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects));
}

void GameplayScene::Start()
{
	GameManager::GetInstance().NewGame("Player1");

	CreateWalls(objects);
	CreateBricks(objects);
	CreatePlayer(objects);
	CreateBall(objects);
}

void GameplayScene::Update()
{
	bool exitScene = false;

	while (!exitScene)
	{
		Sleep(FRAME_DELAY);

		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update();
		}

		exitScene = GetAsyncKeyState('1');

		Render();
	}


	Clear();
	//GameManager::GetInstance().GameFinished();
	nextScene = SceneIndex::MAIN_MENU;
}

void GameplayScene::Clear()
{
	for (GameObject* var : objects)
	{
		delete var;
		objects.clear();
	}
}

void GameplayScene::Render()
{
	system("cls");
	ConsoleSetColor(WHITE, BLACK);

	ConsoleXY(0, MAP_SIZE);
	std::cout << "Player: " + GameManager::GetInstance().GetPlayerName() << std::endl;
	std::cout << "Score " + std::to_string(GameManager::GetInstance().GetPlayerScore());


	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Render();
	}

	ConsoleXY(MAP_SIZE, MAP_SIZE);
}

void GameplayScene::ExitGame()
{
	PlayerStats currentPlayer;

	do
	{
		system("cls");
		std::cout << "----- Quitting game -----\n\nEnter your name: ";
		std::cin >> currentPlayer.playerName;
	} while (currentPlayer.playerName.empty());

	std::fstream saveBinFile;
	int rankedPlayers;
	size_t nameSize;

	saveBinFile.open("Ranking.bin", std::ios::in | std::ios::binary);
	if (!saveBinFile.is_open()) std::cout << "[ERROR] Can't open ranking file.";
	else
	{
		saveBinFile.read(reinterpret_cast<char*>(&rankedPlayers), sizeof(int));
		if (rankedPlayers == 0)
		{
			saveBinFile.close();

			rankedPlayers += 1;
			saveBinFile.open("Ranking.bin", std::ios::out | std::ios::binary);

			nameSize = currentPlayer.playerName.size();
		}
		else
		{
			PlayerStats tmpPlayerStats;
			std::list<PlayerStats> rankedPlayerStats;

			for (int i = 0; i < rankedPlayers; i++)
			{
				saveBinFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
				tmpPlayerStats.playerName.resize(nameSize);
				saveBinFile.read(&tmpPlayerStats.playerName[0], sizeof(char) * nameSize);
				saveBinFile.read(reinterpret_cast<char*>(&tmpPlayerStats.score), sizeof(int));

				rankedPlayerStats.push_back(tmpPlayerStats);
			}
		}
	}
}

//void GamePlayScene::BubbleSort();

void GameplayScene::WriteRankingBin(std::list<PlayerStats> rankedPlayerStats, int rankedPlayers)
{
	std::ofstream saveBinFile;
	if (!saveBinFile.is_open())
	{
		std::cout << "[ERROR] Can't open the file.";
	}
	else
	{
		std::list<PlayerStats>::iterator it;
		it = rankedPlayerStats.begin();
		saveBinFile.write(reinterpret_cast<char*>(&rankedPlayers), sizeof(int));
		for (int i = 0; i < rankedPlayers; i++)
		{
			size_t usernameStrSize = it->playerName.size();

			saveBinFile.write(reinterpret_cast<char*>(&usernameStrSize), sizeof(usernameStrSize));
			saveBinFile.write(it->playerName.c_str(), sizeof(char) * usernameStrSize);
			saveBinFile.write(reinterpret_cast<char*>(&it->score), sizeof(int));
		}
	}
	saveBinFile.close();
}