#include "Animal.h"

Animal::Animal(sf::FloatRect gameArea, float speed,  int minTimeBetweenCrap, int maxTimeBetweenCrap)
	:Entity(speed), gameArea(gameArea), currentDirection(Direction::Left), updateTime(60),timeCounter(0),
	maxTimeBetweenCrap(maxTimeBetweenCrap), minTimeBetweenCrap(minTimeBetweenCrap)
{	
	srand(time(NULL));
	this->setPosition(gameArea.left + gameArea.width / 2.f, 
		gameArea.height / 2.f);

	setCrapTimeInterval(minTimeBetweenCrap, maxTimeBetweenCrap);

}

sf::FloatRect Animal::getGameArea()
{
	return this->gameArea;
}

Direction Animal::getCurrentDirection()
{
	return this->currentDirection;
}

void Animal::setCurrentDirection(Direction dir)
{
	this->currentDirection = dir;
}

bool Animal::isRelieavingWaste()
{
	return this->relieavingWaste;
}

void Animal::setRelieavingWaste(bool status)
{
	this->relieavingWaste = status;
}

void Animal::setCrapTimeInterval(int minTimeBetweenCrap, int maxTimeBetweenCrap)
{
	this->minTimeBetweenCrap = minTimeBetweenCrap;
	this->maxTimeBetweenCrap = maxTimeBetweenCrap;
}

void Animal::move()
{
}


int Animal::getCrapTimeCount() const
{
	return this->crapTimeCount;
}

int Animal::getCrapIntervalCount() const
{
	return crapIntervalCount;
}

void Animal::updateTimeCounter()
{
	timeCounter = (timeCounter + 1) % updateTime;
	if (timeCounter == 0) {

		crapTimeCount = (crapTimeCount + 1) % crapTime;
		crapIntervalCount = (crapIntervalCount + 1) % crapInterval;
	}
}

void Animal::resetCrapTimeInterval()
{
	this->crapInterval = rand() % ((maxTimeBetweenCrap -1 ) - (minTimeBetweenCrap- crapTime )) + (minTimeBetweenCrap+ crapTime);
	crapTimeCount = 0;
	crapIntervalCount = 0;
}

