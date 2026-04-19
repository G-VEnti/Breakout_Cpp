#include "GamePlayScene.h"
#include "Const.h"
#include "Wall.h" 
#include "Pad.h"
#include "Brick.h"
#include "Ball.h"
#include "Vector2.h"
#include "GameManager.h"
#include "Scene.h"
#include "FileManager.h"
#include <string>
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
			GameManager::GetInstance().currentBrikcs++;
		}
	}
}

void GameplayScene::CreatePlayer(std::vector<GameObject*>& objects) {
	objects.push_back(new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 1, MAP_SIZE));
}

void GameplayScene::CreateBall(std::vector<GameObject*>& objects) {
	objects.push_back(new Ball(Vector2(MAP_SIZE / 2, ((MAP_SIZE * 3) / 4) - 5), WHITE, objects));
}

void GameplayScene::Start()
{
	CreateWalls(objects);
	CreateBricks(objects);
	CreatePlayer(objects);
	CreateBall(objects);
}

void GameplayScene::Update()
{
	bool exitScene = false;
	GameManager::GetInstance().SetState(GameState::GAMEPLAY);
	while (GameManager::GetInstance().GetState() == GAMEPLAY)
	{
		Sleep(FRAME_DELAY);

		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update();
		}

		if (GetAsyncKeyState('1'))
		{
			GameManager::GetInstance().SetState(GameState::EXIT);
			break;
		}

		Render();
	}

	ExitGame();

	Clear();
	//GameManager::GetInstance().GameFinished();
	nextScene = SceneIndex::MAIN_MENU;
}

void GameplayScene::Clear()
{
	objects.clear();
	for (GameObject* var : objects)
	{
		delete var;
	}
}

void GameplayScene::Render()
{
	system("cls");
	ConsoleSetColor(WHITE, BLACK);

	ConsoleXY(0, MAP_SIZE);
	std::cout << "Score " + std::to_string(GameManager::GetInstance().GetPlayerScore()) << std::endl;
	std::cout << "Lives: " + std::to_string(GameManager::GetInstance().GetLives()) << std::endl;
	std::cout << "Press 1 to finish current game." << std::endl;
	if (GameManager::GetInstance().IsOnStreak())std::cout << "On Streak! " << std::endl;


	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Render();
	}

	ConsoleXY(MAP_SIZE, MAP_SIZE);
}

void GameplayScene::ExitGame()
{
	PlayerStats currentPlayer;
	std::list<PlayerStats> rankedPlayers;

	// Erase all inputs pressed while playing, AI help
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	system("cls");
	std::cout << "----- Quitting game -----\n\nEnter your name: ";
	std::cin >> currentPlayer.Name;
	if (currentPlayer.Name.empty()) currentPlayer.Name = "ANOnimus";
	currentPlayer.Score = GameManager::GetInstance().GetPlayerScore();

	rankedPlayers = FileManager::ReadRanking();
	rankedPlayers.push_back(currentPlayer);

	if (rankedPlayers.size() == 1)
	{
		FileManager::WriteRanking(rankedPlayers);
	}
	else
	{
		FileManager::RankingSort(rankedPlayers);
		FileManager::WriteRanking(rankedPlayers);
	}
}

