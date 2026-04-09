#include "GameManager.h"
#include <iostream>

GameManager *GameManager::GetInstance()
{
    if (!instance) instance = new GameManager();
    return instance;
}

void GameManager::PrintHi()
{
    std::cout << "hihi";
}
