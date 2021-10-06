#include "Entity.h"



AnimationHelper* Entity::getAnimationHelper()
{
	return this->animationHelper;
}

Entity::Entity(float speed)
	: speed(speed)
{
	animationHelper = new AnimationHelper(sprite);
}

Entity::~Entity()
{
	delete animationHelper;
}

void Entity::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}
 
void Entity::setTexture(std::string texturePath, int nrOfColumns, int nrOfRows, int columnsSubset, int rowsSubset)
{
	this->texture.loadFromFile(texturePath);
	this->sprite.setTexture(this->texture);
	animationHelper->setTexture(this->texture, nrOfColumns, nrOfRows,  columnsSubset,  rowsSubset);
	
}

void Entity::moveSprite(float x, float y)
{
	this->sprite.move(x*speed, y * speed);
}

void Entity::setSpriteScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

sf::FloatRect Entity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

bool Entity::hitBy(const sf::FloatRect& ref)
{
	return this->sprite.getGlobalBounds().intersects(ref);
}

void Entity::update()
{
	this->move();
	this->animationHelper->update();	
}


void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	animationHelper->update();
	target.draw(this->sprite);
}
