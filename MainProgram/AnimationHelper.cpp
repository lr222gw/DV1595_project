#include "AnimationHelper.h"

void AnimationHelper::moveIntRectAtUpdateTime()
{
	if (this->timeCounter == 0) {

		this->intRect.left = (this->intRect.left + this->intRect.width) % this->texture->getSize().x;
		this->sprite->setTextureRect(this->intRect);
	}
}

AnimationHelper::AnimationHelper(sf::Texture& texture, sf::Sprite& sprite, int nrOfColumns, int nrOfRows)
	: timeCounter(0), updateTime(30 )
{
	this->texture = &texture; 
	this->sprite = &sprite;
	this->intRect = sf::IntRect(0, 0, texture.getSize().x / nrOfColumns, texture.getSize().y / nrOfRows);
	this->sprite->setTextureRect(this->intRect);
	lastRow = 1;
}

void AnimationHelper::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		this->sprite->move(-1.f, 0.f);
		this->intRect.top = this->intRect.height * LEFT_ROW;
		lastRow = LEFT_ROW;

		moveIntRectAtUpdateTime();

	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->sprite->move(1.f, 0.f);
		this->intRect.top = this->intRect.height * RIGHT_ROW;		
		lastRow = RIGHT_ROW;
		moveIntRectAtUpdateTime();		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->sprite->move(0.f, -1.f);
		this->intRect.top = this->intRect.height * UP_ROW;
		lastRow = UP_ROW;
		moveIntRectAtUpdateTime();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->sprite->move(0.f, 1.f);
		this->intRect.top = this->intRect.height * DOWN_ROW;
		lastRow = DOWN_ROW;
		moveIntRectAtUpdateTime();
	}
	else{
		this->intRect.top = this->intRect.height * lastRow;		
		if (this->timeCounter == 0) {
			this->intRect.left = 0;
			this->sprite->setTextureRect(this->intRect);
		}
	}

	this->timeCounter = (this->timeCounter + 1) % this->updateTime;
}
