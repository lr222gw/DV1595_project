#include "Entity.h"



Entity::Entity(std::string textureFile, int nrOfColumns, int nrOfRows, float speed)
	: speed(speed)
{
	this->texture.loadFromFile(textureFile);
	this->sprite.setTexture(this->texture);

	animationHelper = new AnimationHelper(texture, sprite, nrOfColumns, nrOfRows);
}

Entity::~Entity()
{
	delete animationHelper;
}

void Entity::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}
 
void Entity::setTexture(std::string texturePath)
{
	this->texture.loadFromFile(texturePath);
	this->sprite.setTexture(this->texture);
	
}

void Entity::moveSprite(float x, float y)
{
	this->sprite.move(x, y);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	animationHelper->update();
	target.draw(this->sprite);
}
