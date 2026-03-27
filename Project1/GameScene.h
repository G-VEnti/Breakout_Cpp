#pragma once
#include "Scene.h"

class GameplayScene : public Scene 
{
public:

	void CreateWalls(std::vector<GameObject*>& objects) {
		for (int i = 0; i < MAP_SIZE; i++) {
			objects.push_back(new Wall(Vector2(i, 0), YELLOW, false));
			objects.push_back(new Wall(Vector2(i, MAP_SIZE - 1), YELLOW, true));

			if (i > 0 && i < MAP_SIZE - 1) {
				objects.push_back(new Wall(Vector2(0, i), YELLOW, false));
				objects.push_back(new Wall(Vector2(MAP_SIZE - 1, i), YELLOW, false));
			}
		}
	}

	void CreateBricks(std::vector<GameObject*>& objects) {
		for (int row = 1; row <= 3; row++) {
			for (int col = 1; col < MAP_SIZE - 1; col++) {
				objects.push_back(new Brick(Vector2(col, row), CYAN));
			}
		}
	}

	void CreatePlayer(std::vector<GameObject*>& objects) {
		objects.push_back(new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 1, MAP_SIZE));
	}

	void CreateBall(std::vector<GameObject*>& objects) {
		objects.push_back(new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects));
	}

	void Start() override
	{
		CreateWalls(objects);
		CreateBricks(objects);
		CreatePlayer(objects);
		CreateBall(objects);
	}

	void Update() override
	{
		bool exitScene = true;

		while (!exitScene)
		{
			Sleep(100);

			for (int i = 0; i < objects.size(); i++) {
				objects[i]->Update();
			}

			exitScene = GetAsyncKeyState('1');

			Render();
		}

		nextScene = SceneIndex::GAMEPLAY;
	}

	void Render() override
	{
		system("cls");
		ConsoleSetColor(WHITE, BLACK);

		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Render();
		}

		ConsoleXY(MAP_SIZE, MAP_SIZE);
	}
};