#include "Animal.h"

Animal::Animal(NumberBoard* theNumberBoard, sf::FloatRect gameArea, float speed,  int minTimeBetweenCrap, int maxTimeBetweenCrap)
	:Entity(speed), gameArea(gameArea), currentDirection(Direction::Left), updateTime(60),timeCounter(0),
	maxTimeBetweenCrap(maxTimeBetweenCrap), minTimeBetweenCrap(minTimeBetweenCrap), theNumberBoard(theNumberBoard)
{	
	
	
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
		// Do something for one whole second...
		
	}
	// Do something only once per second...
	crapTimeCount = (crapTimeCount + 1) % (crapTime * updateTime);
	crapIntervalCount = (crapIntervalCount + 1) % (crapInterval * updateTime);
}

void Animal::resetCrapTimeInterval()
{
	this->crapInterval = rand() % ((maxTimeBetweenCrap -1 ) - (minTimeBetweenCrap- crapTime )) + (minTimeBetweenCrap+ crapTime);
	crapTimeCount = 0;
	crapIntervalCount = 0;
}

