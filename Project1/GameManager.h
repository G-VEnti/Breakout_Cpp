#pragma once
#include <iostream>
#include <vector>
struct PlayerStats
{
	std::string Name = "name";
	int Score = 0;

};

class GameManager
{
public:
	static GameManager& GetInstance();

	int GetPlayerScore();
	std::string GetPlayerName();

	void AddScore(int scoreToAdd);
	
	void GameFinished();
	void NewGame(std::string playerName);


private:
	GameManager(){}
	//save the current player stats to the highscore list,call only when game is over
	void SavePlayerStats();

	//current player stats
	PlayerStats CurrentPlayer;
	//all player higscores
	std::vector<PlayerStats> HighScores;

	//avoid adcidental instanciation
	GameManager(GameManager const&);              
	void operator=(GameManager const&); 

};