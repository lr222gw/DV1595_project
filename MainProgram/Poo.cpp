#include "Poo.h"
Poo::Poo(sf::Vector2f position)
	:Entity(0)
{
	this->setTexture("../Images/sprites/poop.png", 5, 1, 5, 1);
	this->setSpriteScale(.70f, .70f);
	this->getAnimationHelper()->setRowAnimationInstruction(0, 0, 0, 0, 0);
	this->getAnimationHelper()->animateDown();

	this->setPosition(position.x, position.y);
}


void Poo::move()
{
}
