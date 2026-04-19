#pragma once
#include <iostream>
#include <vector>
struct PlayerStats
{
	std::string Name = "name";
	int Score = 0;

};

enum GameState
{
	MAIN_MENU,
	GAMEPLAY,
	EXIT
};

class GameManager
{
public:
	/// <summary>
	/// get reference to the singleton instance game manager,if not instantiated,it will be created
	/// </summary>
	/// <returns>game manager reference</returns>
	static GameManager& GetInstance();

	int GetPlayerScore();
	std::string GetPlayerName();

	void AddScore(int scoreToAdd);
	bool IsOnStreak();
	void LoseStreak();

	GameState GetState();
	void SetState(GameState newState);

	int GetLives();
	void LoseLife(int amout);
	void NewGame(std::string playerName);

	int currentBrikcs;


private:

	GameState currentState = MAIN_MENU;
	GameManager() {}
	//save the current player stats to the highscore list,call only when game is over
	void SavePlayerStats();


	bool onStreak = false;
	int StreakAditive = 5;
	int StreakAmount = 0;

	int lives = 3;
	void GameFinished();

	//current player stats
	PlayerStats CurrentPlayer;
	//all player higscores
	std::vector<PlayerStats> HighScores;

	//avoid adcidental instanciation
	GameManager(GameManager const&);
	void operator=(GameManager const&);
};