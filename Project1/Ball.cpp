#include "Ball.h"
#include "GameManager.h"
#include "Const.h"

void Ball::GetPlayerPad()
{
    for (int i = 0; i < objects->size(); i++) {
        if (Pad* pad = dynamic_cast<Pad*>((*objects)[i])) {
            playerPad.reset(pad);
			objects->push_back(playerPad.get());
            break;
        }
	}

}

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
            GameManager::GetInstance().LoseLife(1);
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

void Ball::HandleCollision(GameObject* other,int indx)
{
    if (!dynamic_cast<Wall*>(other))
    {
        if (Brick* brick = dynamic_cast<Brick*>(other)) {
            brick->Destroy();
            objects->erase(objects->begin() + indx);
        }
        if (Pad* pad = dynamic_cast<Pad*>(other)) {
            //skip bounce it messes padcollisionhandle
            GameManager::GetInstance().LoseStreak();
            HandlePadCollision();
            return;
		}
    }
    Bounce(other);
}

void Ball::HandlePadCollision()
{
    //handle pad collison,middle is handled by default bounce (;
    if (position.y == playerPad->GetPosition().y)
    {
        
        //offsets
        int left = position.x - playerPad->GetWidth();
        int right = position.x + playerPad->GetWidth();


        //left side 
        if (position.x <= playerPad->GetPosition().x - playerPad->GetWidth())
        {
			//with absolute numbers so it always bounces to the same direction without depending on current direction
            direction.x = -abs(direction.x);
			direction.y = -abs(direction.y);
            GameManager::GetInstance().LoseStreak();

        }
        //right
        else if (position.x >= playerPad->GetPosition().x + playerPad->GetWidth())
        {
            direction.x = abs(direction.x);
			direction.y = -abs(direction.y);
			GameManager::GetInstance().LoseStreak();

        }

    }


}

void Ball::Update() {
    if (playerPad == nullptr) GetPlayerPad();
    position.x = position.x + direction.x;
    position.y = position.y + direction.y;

	HandlePadCollision();

    for (int i = 0; i < objects->size(); i++) {
        GameObject* currentObject = (*objects)[i];

        if (currentObject == this) {
            continue;
        }

        if (IsCollidingWith(currentObject)) {
            HandleCollision(currentObject,i);
            break;
        }
    }
}