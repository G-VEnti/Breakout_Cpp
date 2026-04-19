#pragma once
#include "Scene.h"

class CreditsScene : public Scene
{
private:
	void Start() override;
	void Update() override;
	void Render() override;
	void Clear() override;
};