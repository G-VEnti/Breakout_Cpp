#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Wall.h"
#include "Brick.h"
#include "Pad.h"
#include "Ball.h"
#include "Const.h"
#include "Scene.h"
#include "GamePlayScene.h"
#include "MenuScene.h"
#include "RankingScene.h"

int main() {
	srand((unsigned int)time(NULL));

	bool isExitTime = false;


	Scene* myScenes[3];

	myScenes[Scene::MAIN_MENU] = new MenuScene;
	myScenes[Scene::GAMEPLAY] = new GameplayScene;
	myScenes[Scene::RANKING] = new RankingScene;

	Scene::SceneIndex index = Scene::MAIN_MENU;

	while (!isExitTime)
	{
		myScenes[index]->Start();
		myScenes[index]->Update();

		index = myScenes[index]->ChangeScene();

		if (index == Scene::EXIT) isExitTime = true;
	}

	return 0;
}
