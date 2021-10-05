#include "Cow.h"

Cow::Cow(NumberBoard* theNumberBoard,sf::FloatRect gameArea, float speed)
	: Animal(theNumberBoard,gameArea, speed, 10, 30),
	lastCollidedPoo(nullptr), goal(0.f,0.f)
{
	
	this->setTexture("../Images/sprites/cow_2.png",12,8, 3,4);
	this->getAnimationHelper()->setRowAnimationInstruction(3,0,1,2,1);
	this->getAnimationHelper()->toggleReversePlayback();

	this->setSpriteScale(.5f,.5f);
	this->setDirectionToAorB(Direction::Left,Direction::Right);
	this->setPosition(gameArea.left + (gameArea.width / 10.f) * (rand() % (9-1) + 1),
		(gameArea.height/ 10.f) * (rand() % (9 - 1) + 1));
}

bool Cow::hasGoal()
{
	return goal != sf::Vector2f(0.f,0.f);
}

void Cow::setDirectionToAorB(Direction alternativeOne, Direction alternativeTwo)
{
	bool selectDirection = (rand() % 2 == 0);
	if (selectDirection)
	{
		this->setCurrentDirection(alternativeOne);
	}
	else {
		this->setCurrentDirection(alternativeTwo);
	}
}

void Cow::move()
{
	if (hasGoal()) {
		
		float length = sqrt(goal.x * goal.x + goal.y * goal.y);
		sf::Vector2f normalized(goal.x / length, goal.y / length);
		this->moveSprite(normalized.x, normalized.y);
		if (normalized.x < -0.6 || normalized.x > 0.6) {
			if (normalized.x < 0) {
				this->getAnimationHelper()->animateLeft();
			}
			else {
				this->getAnimationHelper()->animateRight();
			}
		}
		else if (normalized.y < 0) {
			this->getAnimationHelper()->animateUp();
		}
		else if (normalized.y > 0) {
			this->getAnimationHelper()->animateDown();
		}
	}
	else {
		if (!this->isRelieavingWaste()) {


			Poo* collidedPoo = theNumberBoard->collidedWithPoo(*this);
			if (collidedPoo && lastCollidedPoo != collidedPoo) {

				if (this->getCurrentDirection() == Direction::Left)
				{
					setDirectionToAorB(Direction::Up, Direction::Down);

				}
				else if (this->getCurrentDirection() == Direction::Up)
				{
					setDirectionToAorB(Direction::Right, Direction::Left);
				}
				else if (this->getCurrentDirection() == Direction::Right)
				{
					setDirectionToAorB(Direction::Down, Direction::Up);
				}
				else if (this->getCurrentDirection() == Direction::Down)
				{
					setDirectionToAorB(Direction::Left, Direction::Right);
				}

				lastCollidedPoo = collidedPoo;
			}

			if (getCurrentDirection() == Direction::Left) {

				if (this->getGameArea().left < this->getBounds().left) {

					this->getAnimationHelper()->animateLeft();
					this->moveSprite(LEFT, 0.f);
				}
				else {
					this->setCurrentDirection(Direction::Up);
				}
			}
			else if (getCurrentDirection() == Direction::Right) {
				if (this->getGameArea().left + this->getGameArea().width > this->getBounds().left + this->getBounds().width) {

					this->getAnimationHelper()->animateRight();
					this->moveSprite(RIGHT, 0.f);
				}
				else {
					this->setCurrentDirection(Direction::Down);
				}
			}
			else if (getCurrentDirection() == Direction::Up) {
				if (this->getGameArea().top < this->getBounds().top) {

					this->getAnimationHelper()->animateUp();
					this->moveSprite(0.f, UP);
				}
				else {
					this->setCurrentDirection(Direction::Right);
				}
			}
			else if (getCurrentDirection() == Direction::Down) {
				if (this->getGameArea().top + this->getGameArea().height > this->getBounds().top + this->getBounds().height) {

					this->getAnimationHelper()->animateDown();
					this->moveSprite(0.f, DOWN);
				}
				else {
					this->setCurrentDirection(Direction::Left);
				}
			}
		}
		else {

			if (getCrapTimeCount() == 0) {
				setRelieavingWaste(false);
				crapOnTile();
			}
		}

		if (getCrapIntervalCount() == 0) {
			this->getAnimationHelper()->animateIdle();
			setRelieavingWaste(true);
			resetCrapTimeInterval();
		}
	}
	

}

void Cow::setGoal(sf::Vector2f pos)
{
	this->goal = pos;
}

void Cow::crapOnTile()
{
	sf::Vector2f posCowsButt;
	if (currentDirection == Direction::Down) {
		posCowsButt.x = this->getBounds().left + this->getBounds().width/4;
		posCowsButt.y = this->getBounds().top;
	}
	else if (currentDirection == Direction::Up) {
		posCowsButt.x = this->getBounds().left + this->getBounds().width / 4;
		posCowsButt.y = this->getBounds().top + this->getBounds().height;
	}
	else if (currentDirection == Direction::Left) {
		posCowsButt.x = this->getBounds().left + this->getBounds().width;
		posCowsButt.y = this->getBounds().top + this->getBounds().height / 4; 
	}
	else if (currentDirection == Direction::Right) {
		
		posCowsButt.x = this->getBounds().left;
		posCowsButt.y = this->getBounds().top + this->getBounds().height / 4;
	
	}
	Poo* poo = new Poo(posCowsButt);
	this->theNumberBoard->recievePoo(poo);
	this->theNumberBoard->markTileAsCrapped(poo->getBounds());
}
