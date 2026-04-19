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
			position.x = MAP_SIZE / 2;
			position.y = ((MAP_SIZE * 3) / 4) - 5;
			direction.x = 0;
			direction.y = -1;
		}
	}

	bool bounceHorizontal = hasObjectAbove || hasObjectBelow;
	bool bounceVertical = hasObjectLeft || hasObjectRight;

	//top bottom
	if (bounceVertical) {
		direction.x = -direction.x;
		direction.y = -direction.y;

	}

	//sides 
	if (bounceHorizontal) {
		direction.x = -direction.x;
		//direction.y = -direction.y;
	}

}

void Ball::HandleCollision(GameObject* other, int indx)
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
			//HandlePadCollision();
			//return;
		}
	}
	Bounce(other);
}

void Ball::HandlePadCollision()
{
	//handle pad collison,middle is handled by default bounce (;
	if (position.y == playerPad->GetPosition().y &&
		(position.x == playerPad->GetPosition().x ||
			position.x == playerPad->GetPosition().x - 1 ||
			position.x == playerPad->GetPosition().x + 1)) {
		//offsets
		int left = position.x - playerPad->GetWidth();
		int right = position.x + playerPad->GetWidth();

		//left side 
		if (position.x <= playerPad->GetPosition().x - playerPad->GetWidth())
		{
			//with absolute numbers so it always bounces to the same direction without depending on current direction
			direction.x = -1;
			direction.y = -abs(direction.y);
			GameManager::GetInstance().LoseStreak();
		}
		//right
		else if (position.x >= playerPad->GetPosition().x + playerPad->GetWidth())
		{
			direction.x = 1;
			direction.y = -abs(direction.y);
			GameManager::GetInstance().LoseStreak();
		}
		else
		{
			direction.y = -abs(direction.y);
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
			HandleCollision(currentObject, i);
			break;
		}
	}

	if (position.x >= MAP_SIZE)
	{
		position.x = MAP_SIZE - 1;
		direction.x = -1;
	}
	if (position.x <= 0)
	{
		position.x = 1;
		direction.x = 1;
	}
	if (position.y < 0)
	{
		position.y = 1;
		direction.y = 1;
	}

	if (playerPad == nullptr) GetPlayerPad();
	HandlePadCollision();
}