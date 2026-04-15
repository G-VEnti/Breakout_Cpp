#pragma once
#include <string>
#include <list>
#include "Scene.h"
#include "Const.h"
#include "GameManager.h"

class FileManager
{

public:
	static const std::string binFileName;

	static std::list<PlayerStats> ReadRanking();
	static void WriteRanking(std::list<PlayerStats> rankedPlayerStats);
	static std::string RankingToString(std::list<PlayerStats> rankedPlayerStats);
};