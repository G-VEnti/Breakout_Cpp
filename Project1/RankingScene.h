#pragma once
#include "Scene.h"
#include "GameManager.h"
#include <iostream>
#include <list>

class RankingScene : public Scene
{
private:
	std::list<PlayerStats> rankedPlayers;
	std::string ranking;

	void Start() override;
	void Update() override;
	void Render() override;
	void Clear() override;
};