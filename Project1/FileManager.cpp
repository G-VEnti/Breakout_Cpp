#include "FileManager.h"
#include <fstream>

const std::string FileManager::binFileName = "Ranking.bin";

void SaveScore(PlayerStats playerInfo)
{

}

std::list<PlayerStats> FileManager::ReadRanking()
{
#pragma region dataInsertTest


	/*std::fstream saveBinFile;
	PlayerStats actualPlayer;
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
			std::cin >> actualPlayer.playerName;
			std::cout << "Enter score: ";
			std::cin >> actualPlayer.score;

			size_t usernameStrSize = actualPlayer.playerName.size();

			saveBinFile.write(reinterpret_cast<char*>(&usernameStrSize), sizeof(usernameStrSize));
			saveBinFile.write(actualPlayer.playerName.c_str(), sizeof(char) * usernameStrSize);
			saveBinFile.write(reinterpret_cast<char*>(&actualPlayer.score), sizeof(int));
		}
	}
	saveBinFile.close();*/
#pragma endregion

	std::list<PlayerStats> rankedPlayerStats;
	std::ifstream saveBinFile;
	PlayerStats player;
	int playersInRanking;
	size_t nameSize;

	saveBinFile.open(binFileName, std::ios::in | std::ios::binary);
	if (!saveBinFile.is_open()) std::cout << "[ERROR] Can't open ranking file.";
	else
	{
		saveBinFile.read(reinterpret_cast<char*>(&playersInRanking), sizeof(int));
		for (int i = 0; i < playersInRanking; i++)
		{
			saveBinFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
			player.Name.resize(nameSize);
			saveBinFile.read(&player.Name[0], sizeof(char) * nameSize);
			saveBinFile.read(reinterpret_cast<char*>(&player.Score), sizeof(int));
			rankedPlayerStats.push_back(player);
			//ranking += std::to_string(i + 1) + ". " + player.Name + " Score = " + std::to_string(player.Score) + ".\n";
		}
	}
	saveBinFile.close();

	return rankedPlayerStats;
}

void FileManager::WriteRanking(std::list<PlayerStats> rankedPlayerStats)
{
	int playersInRanking = rankedPlayerStats.size();
	if (playersInRanking > MAX_RANKED_PLAYERS) playersInRanking = MAX_RANKED_PLAYERS;
	std::ofstream saveBinFile;
	saveBinFile.open(binFileName, std::ios::out | std::ios::binary);
	if (!saveBinFile.is_open()) std::cout << "[ERROR] Can't open the file.";
	else
	{
		std::list<PlayerStats>::iterator it;
		it = rankedPlayerStats.begin();
		saveBinFile.write(reinterpret_cast<char*>(&playersInRanking), sizeof(int));
		for (int i = 0; i < playersInRanking; i++, it++)
		{
			size_t usernameStrSize = it->Name.size();
			saveBinFile.write(reinterpret_cast<char*>(&usernameStrSize), sizeof(usernameStrSize));
			saveBinFile.write(it->Name.c_str(), sizeof(char) * usernameStrSize);
			saveBinFile.write(reinterpret_cast<char*>(&it->Score), sizeof(int));
		}
	}
	saveBinFile.close();
}

std::string FileManager::RankingToString(std::list<PlayerStats> rankedPlayerStats)
{
	std::string ranking;
	std::list<PlayerStats>::iterator it = rankedPlayerStats.begin();

	for (int i = 0; i < rankedPlayerStats.size(); i++, it++)
	{
		ranking += std::to_string(i + 1) + ". " + it->Name + " Score = " + std::to_string(it->Score) + ".\n";
	}

	return ranking;
}
