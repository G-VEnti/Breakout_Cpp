#include "GameScene.h"
#include "Const.h"
#include "Wall.h" 
#include "Pad.h"
#include "Brick.h"
#include "Ball.h"
#include "Vector2.h"

void GameplayScene::CreateWalls(std::vector<GameObject*>& objects) {
	for (int i = 0; i < MAP_SIZE; i++) {
		objects.push_back(new Wall(Vector2(i, 0), YELLOW, false));
		objects.push_back(new Wall(Vector2(i, MAP_SIZE - 1), YELLOW, true));

		if (i > 0 && i < MAP_SIZE - 1) {
			objects.push_back(new Wall(Vector2(0, i), YELLOW, false));
			objects.push_back(new Wall(Vector2(MAP_SIZE - 1, i), YELLOW, false));
		}
	}
}

void GameplayScene::CreateBricks(std::vector<GameObject*>& objects) {
	for (int row = 1; row <= 3; row++) {
		for (int col = 1; col < MAP_SIZE - 1; col++) {
			objects.push_back(new Brick(Vector2(col, row), CYAN));
		}
	}
}

void GameplayScene::CreatePlayer(std::vector<GameObject*>& objects) {
	objects.push_back(new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 1, MAP_SIZE));
}

void GameplayScene::CreateBall(std::vector<GameObject*>& objects) {
	objects.push_back(new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects));
}

void GameplayScene::Start()
{
	CreateWalls(objects);
	CreateBricks(objects);
	CreatePlayer(objects);
	CreateBall(objects);
}

void GameplayScene::Update()
{
	bool exitScene = false;

	while (!exitScene)
	{
		Sleep(100);

		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update();
		}

		exitScene = GetAsyncKeyState('1');

		Render();
	}


	Clear();
	nextScene = SceneIndex::MAIN_MENU;
}
void GameplayScene::Clear() {


	/*for (GameObject* var : objects)
	{
		printf(dynamic_cast<Ball*>(var) == nullptr);
		if (typeid(var).name() == "b") {
			delete var;
		}
	}
	*/

}

void GameplayScene::Render()
{
	system("cls");
	ConsoleSetColor(WHITE, BLACK);

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Render();
	}

	ConsoleXY(MAP_SIZE, MAP_SIZE);
}