#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Vector2.h"

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
};