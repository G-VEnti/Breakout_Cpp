#pragma once
#include "Scene.h"
#include <iostream>

class MenuScene : public Scene
{
	void Start() override
	{

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
		std::cout << "Menu, press 1 to continue:";
	}
};