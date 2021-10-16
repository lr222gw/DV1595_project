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

void Entity::setSpriteColor(sf::Color color)
{
	this->sprite.setColor(color);
}

void Entity::resetSpriteColor()
{
	this->sprite.setColor(sf::Color::Color(255,255,255,255));
}

sf::FloatRect Entity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

bool Entity::hitBy(const sf::FloatRect& ref)
{
	sf::FloatRect smallerHitBox;
	smallerHitBox.width = this->sprite.getGlobalBounds().width / 2.f;
	smallerHitBox.height = this->sprite.getGlobalBounds().height / 2.f;
	smallerHitBox.left = this->sprite.getGlobalBounds().left + smallerHitBox.width / 2.f;
	smallerHitBox.top = this->sprite.getGlobalBounds().top + smallerHitBox.height / 2.f;

	sf::FloatRect refSmallerHitBox = ref;
	refSmallerHitBox.width = ref.width / 2.f;
	refSmallerHitBox.height = ref.height / 2.f;
	refSmallerHitBox.left = ref.left + refSmallerHitBox.width / 2.f;
	refSmallerHitBox.top = ref.top + refSmallerHitBox.height / 2.f;
	
	return smallerHitBox.intersects(refSmallerHitBox);
	//return this->sprite.getGlobalBounds().intersects(ref);
}

void Entity::update()
{
	this->move();		
	this->animationHelper->update();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{		
	auto floatRect = this->sprite.getGlobalBounds();

	//Collision Debug...

	sf::FloatRect smallerHitBox;
	smallerHitBox.width = this->sprite.getGlobalBounds().width / 2.f;
	smallerHitBox.height = this->sprite.getGlobalBounds().height / 2.f;
	smallerHitBox.left = this->sprite.getGlobalBounds().left + smallerHitBox.width / 2.f;
	smallerHitBox.top = this->sprite.getGlobalBounds().top + smallerHitBox.height / 2.f;

	sf::RectangleShape rectTop(sf::Vector2f(smallerHitBox.width, 2.f));
	rectTop.setPosition(smallerHitBox.left, smallerHitBox.top);
	rectTop.setFillColor(sf::Color::White);

	sf::RectangleShape rectLeft(sf::Vector2f(2.f, smallerHitBox.height));
	rectLeft.setPosition(smallerHitBox.left, smallerHitBox.top);
	rectLeft.setFillColor(sf::Color::White);

	sf::RectangleShape rectRight(sf::Vector2f(2.f, smallerHitBox.height));
	rectRight.setPosition(smallerHitBox.left + smallerHitBox.width, smallerHitBox.top);
	rectRight.setFillColor(sf::Color::White);

	sf::RectangleShape rectBottom(sf::Vector2f(smallerHitBox.width, 2.f));
	rectBottom.setPosition(smallerHitBox.left, smallerHitBox.top + smallerHitBox.height);
	rectBottom.setFillColor(sf::Color::White);

	

	target.draw(this->sprite);
	//target.draw(rectTop);
	//target.draw(rectLeft);
	//target.draw(rectRight);
	//target.draw(rectBottom);
}
 