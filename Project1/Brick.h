#pragma once
#include "GameObject.h"
#include "GameManager.h"
class Brick : public GameObject {
protected:
	bool destroyed;
public:
	Brick(Vector2 _pos, ConsoleColor c)
		: GameObject(_pos, '=', c), destroyed(false) {}
	inline bool GetDestroyed() const { return destroyed; }
	int Score = 15;
	inline void Destroy() { 
		destroyed = true; 
		GameManager::GetInstance().AddScore(Score);
	}

	void Render() override {
		if (!destroyed) {
			GameObject::Render();
		}
	}
};