#pragma once
#include "Scene.h"
#include <iostream>

class RankingScene : public Scene
{
private:
	std::string ranking;

	void Start() override;
	void Update() override;
	void Render() override;
	void Clear() override;
	std::string ReadBin();
};