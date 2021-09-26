#include "Cow.h"

Cow::Cow(NumberBoard* theNumberBoard,sf::FloatRect gameArea, float speed)
	: Animal(theNumberBoard,gameArea, speed, 5, 10)
{
	this->setTexture("../Images/sprites/cow.png",12,8, 3,4);
	this->getAnimationHelper()->setRowAnimationInstruction(3,0,1,2,1);
	this->getAnimationHelper()->toggleReversePlayback();
	this->setSpriteScale(2.f,2.f);

	this->setCurrentDirection(Direction::Left);
}

void Cow::move()
{
	if (!this->isRelieavingWaste()) {

		if (Poo* collidedPoo = theNumberBoard->collidedWithPoo(*this)) {
			if (collidedPoo->getBounds().left < this->getBounds().left  ) {
				currentDirection = Direction::Up;
			}
			else if (collidedPoo->getBounds().left + collidedPoo->getBounds().width < this->getBounds().left + this->getBounds().width) {
				currentDirection = Direction::Down;
			}
			else if (collidedPoo->getBounds().top < this->getBounds().top) {
				currentDirection = Direction::Left;
			}
			else if (collidedPoo->getBounds().top - collidedPoo->getBounds().height > this->getBounds().top) {
				currentDirection = Direction::Right;
			}
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

	if (getCrapIntervalCount() == 0 ) {
		this->getAnimationHelper()->animateIdle();
		setRelieavingWaste(true);
		resetCrapTimeInterval();		
	}
	

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
