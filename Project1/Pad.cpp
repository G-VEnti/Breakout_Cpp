#include "Pad.h"

void Pad::Update() {
    bool moveLeft = GetAsyncKeyState('A') != 0;
    bool moveRight = GetAsyncKeyState('D') != 0;

    if (moveLeft) {
        bool canMoveLeft = position.x - width > 1;
        if (canMoveLeft) {
            position.x = position.x - 1;
        }
    }

    if (moveRight) {
        bool canMoveRight = position.x + width < mapSize - 2;
        if (canMoveRight) {
            position.x = position.x + 1;
        }
    }
}

void Pad::Render() {
    GameObject::Render();

    for (int i = 1; i <= width; i++) {
        ConsoleXY(position.x + i, position.y);
        std::cout << charToPrint;

        ConsoleXY(position.x - i, position.y);
        std::cout << charToPrint;
    }
}