#pragma once
#include <list>
#include "Scene.h"
#include "GameObject.h"
#include <list>
#include "Vector2.h"
#include "FileManager.h"

class GameplayScene : public Scene 
{
public:

	void CreateWalls(std::vector<GameObject*>& objects);
	void CreateBricks(std::vector<GameObject*>& objects);
	void CreatePlayer(std::vector<GameObject*>& objects);
	void CreateBall(std::vector<GameObject*>& objects);


	void Start() override;
	void Update() override;
	void Clear() override;
	void Render() override;

	void ExitGame();
	void WriteRankingBin(std::list<PlayerStats> rankedPlayerStats, int rankedPlayers);
	//void BubbleSort(std::list<PlayerStats> rankedPlayerStats);
};