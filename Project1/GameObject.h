#pragma once
#include "Vector2.h"
#include "ConsoleControl.h"

class GameObject {
protected:
    Vector2 position;
    char charToPrint;
    ConsoleColor color;

public:
    GameObject(Vector2 newPosition, char newChar, ConsoleColor newColor) {
        position = newPosition;
        charToPrint = newChar;
        color = newColor;
    }

    Vector2 GetPosition() const {
        return position;
    }

    char GetCharToPrint() const {
        return charToPrint;
    }

    virtual void Update() {
    }

    virtual void Render();
};