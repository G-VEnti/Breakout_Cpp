#pragma once
#include "GameObject.h"

class Brick : public GameObject {
protected:
	bool destroyed;
public:
	Brick(Vector2 _pos, ConsoleColor c)
		: GameObject(_pos, '=', c), destroyed(false) {}
	inline bool GetDestroyed() const { return destroyed; }
	inline void Destroy() { destroyed = true; }

	void Render() override {
		if (!destroyed) {
			GameObject::Render();
		}
	}
};