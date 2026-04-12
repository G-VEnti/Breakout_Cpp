#include "Ball.h"
#include "GameManager.h"
#include "Const.h"

bool Ball::IsCollidingWith(GameObject* other) {


    return position == other->GetPosition();
}

//also handles Wall collision
bool Ball::HasObjectAtPosition(int x, int y) {
    Vector2 targetPosition(x, y);

    for (int i = 0; i < objects->size(); i++) {
        if ((*objects)[i] == this) {
            continue;
        }

        if ((*objects)[i]->GetPosition() == targetPosition) {
            return true;
        }
    }

    return false;
}

void Ball::Bounce(GameObject* other) {
    Vector2 otherPosition = other->GetPosition();

    bool hasObjectAbove = HasObjectAtPosition(otherPosition.x, otherPosition.y - 1);
    bool hasObjectBelow = HasObjectAtPosition(otherPosition.x, otherPosition.y + 1);
    bool hasObjectLeft = HasObjectAtPosition(otherPosition.x - 1, otherPosition.y);
    bool hasObjectRight = HasObjectAtPosition(otherPosition.x + 1, otherPosition.y);

    //out of bounds collision
    if (Wall* wall = dynamic_cast<Wall*>(other)) {
        if (wall->GetIsBottom()) {
            GameManager::GetInstance().GameFinished();
        }
    }
    bool bounceHorizontal = hasObjectAbove || hasObjectBelow;
    bool bounceVertical = hasObjectLeft || hasObjectRight;

    if (!bounceHorizontal && !bounceVertical) {
        direction.x = -direction.x;
        direction.y = -direction.y;
        return;
    }

    if (bounceVertical) {
        direction.y = -direction.y;
    }

    if (bounceHorizontal) {
        direction.x = -direction.x;
    }
}

void Ball::HandleCollision(GameObject* other)
{
    if (!dynamic_cast<Wall*>(other) && !dynamic_cast<Pad*>(other))
    {
        if (Brick* brick = dynamic_cast<Brick*>(other)) {
            brick->Destroy();
        }
    }
}

void Ball::Update() {
    position.x = position.x + direction.x;
    position.y = position.y + direction.y;

    for (int i = 0; i < objects->size(); i++) {
        GameObject* currentObject = (*objects)[i];

        if (currentObject == this) {
            continue;
        }

        if (IsCollidingWith(currentObject)) {
            Bounce(currentObject);
            HandleCollision(currentObject);

            break;
        }
    }
}