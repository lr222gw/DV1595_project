#include "Entity.h"



void Entity::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}
 
void Entity::setTexture(std::string texturePath)
{
	this->texture.loadFromFile(texturePath);
	this->sprite.setTexture(this->texture);
	this->intRect = sf::IntRect(0, 0, texture.getSize().x / 8, texture.getSize().y / 2);
	this->sprite.setTextureRect(this->intRect);
}

void Entity::moveSprite(float x, float y)
{
	this->sprite.move(x, y);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
