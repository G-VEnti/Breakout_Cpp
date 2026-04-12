#include "GameManager.h"
#include "ConsoleControl.h"
#include "Const.h"
GameManager& GameManager::GetInstance()
{
	//destroyed or instanciated on first use
	static GameManager instance;
	return instance;
}

int GameManager::GetPlayerScore()
{
	return CurrentPlayer.Score;
}

std::string GameManager::GetPlayerName()
{
	return CurrentPlayer.Name;
}

void GameManager::AddScore(int scoreToAdd)
{
	CurrentPlayer.Score += scoreToAdd;
}

void GameManager::GameFinished()
{
	ConsoleXY(0,MAP_SIZE+4);
	std::cout << "Game Finished!" << std::endl;
	SavePlayerStats();
	//debug
	quick_exit(0);

}

void GameManager::NewGame(std::string playerName)
{
	//make sure reset stats for new game
	CurrentPlayer = PlayerStats{ playerName, 0 };
}

void GameManager::SavePlayerStats()
{
	std::cout << "Player Name: " << CurrentPlayer.Name << ", Score: " << CurrentPlayer.Score << std::endl;
	HighScores.push_back(CurrentPlayer);
}
