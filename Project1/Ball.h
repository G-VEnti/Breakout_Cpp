#pragma once
#include "GameObject.h"
#include "Wall.h"
#include "Brick.h"
#include "Pad.h"

#include <vector>

class Ball : public GameObject {
private:
    Vector2 direction;
    std::vector<GameObject*>* objects;

	//reference to player pad for collision handling
	std::unique_ptr<Pad> playerPad = nullptr;
	void GetPlayerPad();

    bool IsCollidingWith(GameObject* other);
    bool HasObjectAtPosition(int x, int y);
    void Bounce(GameObject* other);

	void HandleCollision(GameObject* other,int indx);
	/// <summary>
	/// handled separatly for side detection(they arent recognized by default bounce)
	/// </summary>
	void HandlePadCollision();

public:
    Ball(Vector2 newPosition, ConsoleColor newColor, std::vector<GameObject*>& gameObjects)
        : GameObject(newPosition, '@', newColor) {
        direction = Vector2(1, 1);
        objects = &gameObjects;
    }

    void Update() override;
};