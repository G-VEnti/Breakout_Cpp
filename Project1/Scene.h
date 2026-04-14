#pragma once
#include <vector>
#include <iostream>
#include "GameInput.h"
#include "GameObject.h"

class Scene
{
public:
	enum SceneIndex { MAIN_MENU, GAMEPLAY, RANKING, EXIT };

protected:

	std::vector<GameObject*> objects;
	SceneIndex nextScene;
	struct PlayerStats
	{
		std::string playerName = "";
		int score = 0;
	};


	Scene() {};
	//~Scene() {};

public:

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clear() = 0;

	SceneIndex ChangeScene()
	{
		return nextScene;
	}
};