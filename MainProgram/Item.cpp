#include "Item.h"
#include "Player.h"

Item::Item(float speed, int price)
	: Entity(speed), shouldTerminate(false), price(price)
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

int Item::getPrice() const
{
	return this->price;
}

