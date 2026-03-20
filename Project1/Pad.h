#pragma once
#include "GameObject.h"
#include <Windows.h>

class Pad : public GameObject {
private:
    int width;
    int mapSize;

public:
    Pad(Vector2 newPosition, ConsoleColor newColor, int newWidth, int newMapSize)
        : GameObject(newPosition, '_', newColor) {
        width = newWidth;
        mapSize = newMapSize;
    }

    int GetWidth() const {
        return width;
    }

    void Update() override;
    void Render() override;
};