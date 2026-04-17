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
	if (onStreak) {
		StreakAmount += StreakAditive;
		scoreToAdd += StreakAmount;
	}
	CurrentPlayer.Score += scoreToAdd;
	onStreak = true;
	currentBrikcs--;
	if (currentBrikcs <= 0) {
		GameFinished();
	}
}

bool GameManager::IsOnStreak()
{
	return onStreak;
}

int GameManager::GetLives() { return lives; }

void GameManager::LoseLife(int amount = 1)
{
	lives--;
	LoseStreak();
	if (lives <= 0) {
		GameFinished();
	}

}

void GameManager::GameFinished()
{
	ConsoleXY(0,MAP_SIZE+4);
	std::cout << "Game Finished!" << std::endl;
	SetState(EXIT);
	SavePlayerStats();
	//debug

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

void GameManager::LoseStreak() { 
	onStreak = false; 
	StreakAmount = 0; 

}

gameState GameManager::GetState()
{
	return currentState;
}

void GameManager::SetState(gameState newState)
{
	currentState = newState;

}
