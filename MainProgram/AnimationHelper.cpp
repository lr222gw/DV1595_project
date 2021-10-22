#include "AnimationHelper.h"

void AnimationHelper::moveIntRectAtUpdateTime(bool forceUpdate = false)
{
	if (this->timeCounter == 0 || forceUpdate) {

		if (reversePlayback) {

			if (rightDir_playback) {

				this->intRect.left = (this->intRect.left + this->intRect.width) % (this->intRect.width * (this->columnsSubset));
				if (this->intRect.left == 0) {
					this->intRect.left = (this->intRect.width * (this->columnsSubset-2));
					rightDir_playback = !rightDir_playback;
				}
			}
			else {
				this->intRect.left = (this->intRect.left - this->intRect.width) % (this->intRect.width * (this->columnsSubset));				
			}
			this->sprite->setTextureRect(this->intRect);
			if (this->intRect.left == 0) {
				rightDir_playback = !rightDir_playback;
			}
			
		}
		else {

			this->intRect.left = (this->intRect.left + this->intRect.width ) % ((this->intRect.width) * (this->columnsSubset));
			this->sprite->setTextureRect(this->intRect);
			
		}		
	}
}

AnimationHelper::AnimationHelper(sf::Sprite& sprite)
	: timeCounter(0), updateTime(15 ), nrOfRows(0), nrOfColumns(0), reversePlayback(false), rightDir_playback(true)
{
	this->texture = nullptr;
	down_row = 0;
	up_row = 1;
	left_row = 2;
	right_row = 3;
	idle_column = 4;	
	this->sprite = &sprite;
	
	lastRow = 1;
	animationDirection = idle_column;
}

void AnimationHelper::setTexture(sf::Texture& texture, int nrOfColumns, int nrOfRows, int columnsSubset, int rowsSubset)
{
	this->texture = &texture;
	this->intRect = sf::IntRect(0, 0, texture.getSize().x / nrOfColumns, texture.getSize().y / nrOfRows);
	this->sprite->setTextureRect(this->intRect);
	this->nrOfRows = nrOfRows;
	this->nrOfColumns = nrOfColumns;
	this->columnsSubset = columnsSubset ; // remove one. Makes index start at 0 instead of 1...
	this->rowsSubset = rowsSubset ;
}

void AnimationHelper::toggleReversePlayback()
{
	this->reversePlayback = !this->reversePlayback;
}

bool AnimationHelper::isCurrentDirectionDown()
{
	return lastRow == this->down_row;
}

bool AnimationHelper::isCurrentDirectionUp()
{
	return lastRow == this->up_row;
}

bool AnimationHelper::isCurrentDirectionLeft()
{
	return lastRow == this->left_row;
}
bool AnimationHelper::isCurrentDirectionRight()
{
	return lastRow == this->right_row;
}

void AnimationHelper::setRowAnimationInstruction(int up, int down, int left, int right, int idle)
{
	down_row = down;
	up_row = up;
	left_row = left;
	right_row = right;
	idle_column = idle;
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
	//else if (animationDirection == idle_column) 
	else
	{
		this->intRect.top = this->intRect.height * lastRow;		
		if (this->timeCounter == 0) {
			this->intRect.left = idle_column * this->intRect.width;
			this->sprite->setTextureRect(this->intRect);
		}
	}

	this->timeCounter = (this->timeCounter + 1) % this->updateTime;
}

void AnimationHelper::forceUpdate()
{
	update();
	moveIntRectAtUpdateTime(true);
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
	animationDirection = -1;
}
