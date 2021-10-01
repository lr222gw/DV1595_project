#include "Item.h"
#include "Player.h"

Item::Item(float speed)
	: Entity(speed), shouldTerminate(false)
{
}

bool Item::isTerminated()
{
	return shouldTerminate;
}

void Item::terminate()
{
	this->shouldTerminate = true;
}

