#include "Item.h"
#include "Player.h"

Item::Item(float speed, int price, float defaultScale, float thumbnailScale)
	: Entity(speed), shouldTerminate(false), price(price), defaultScale(defaultScale), thumbnailScale(thumbnailScale)
{
	this->setDefaultScale();
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

void Item::setDefaultScale()
{
	this->setSpriteScale(defaultScale, defaultScale);
}

void Item::setThumbnailScale()
{
	this->setSpriteScale(thumbnailScale, thumbnailScale);
}

void Item::resetItem()
{
	this->shouldTerminate = false;
	this->setThumbnailScale();
	this->setPosition(-100.f,-100.f);
	this->getAnimationHelper()->animateIdle();

	this->resetItemSpecifics();
}

