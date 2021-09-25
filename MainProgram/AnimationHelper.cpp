#include "AnimationHelper.h"

void AnimationHelper::moveIntRectAtUpdateTime()
{
	if (this->timeCounter == 0) {

		this->intRect.left = (this->intRect.left + this->intRect.width) % this->texture->getSize().x;
		this->sprite->setTextureRect(this->intRect);
	}
}

AnimationHelper::AnimationHelper(sf::Sprite& sprite)
	: timeCounter(0), updateTime(60 )
{
	down_row = 0;
	up_row = 1;
	left_row = 2;
	right_row = 3;
	idle_row = -1;	
	this->sprite = &sprite;
	
	lastRow = 1;
	animationDirection = idle_row;
}

void AnimationHelper::setTexture(sf::Texture& texture, int nrOfColumns, int nrOfRows)
{
	this->texture = &texture;
	this->intRect = sf::IntRect(0, 0, texture.getSize().x / nrOfColumns, texture.getSize().y / nrOfRows);
	this->sprite->setTextureRect(this->intRect);
}

void AnimationHelper::setRowAnimationInstruction(int up, int down, int left, int right)
{
	down_row = down;
	up_row = up;
	left_row = left;
	right_row = right;
}

void AnimationHelper::update()
{

	if (animationDirection == left_row) 
	{
		this->intRect.top = this->intRect.height * left_row;
		lastRow = left_row;

		moveIntRectAtUpdateTime();

	}
	else if (animationDirection == right_row) 
	{
		this->intRect.top = this->intRect.height * right_row;
		lastRow = right_row;
		moveIntRectAtUpdateTime();		
	}
	else if (animationDirection == up_row) 
	{
		this->intRect.top = this->intRect.height * up_row;
		lastRow = up_row;
		moveIntRectAtUpdateTime();
	}	
	else if (animationDirection == down_row) 
	{
		this->intRect.top = this->intRect.height * down_row;
		lastRow = down_row;
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

void AnimationHelper::animateDown() {
	animationDirection = down_row;
}
void AnimationHelper::animateUp()
{
	animationDirection = up_row;
}

void AnimationHelper::animateLeft()
{
	animationDirection = left_row;
}

void AnimationHelper::animateRight()
{
	animationDirection = right_row;
}

void AnimationHelper::animateIdle()
{
	animationDirection = idle_row;
}
