#pragma once
#include "Scene.h"
#include <iostream>

class MenuScene : public Scene
{
	
	void Start() override;
	void Update() override;
	void Render() override;
	void Clear() override;

	bool ChooseScene();
};