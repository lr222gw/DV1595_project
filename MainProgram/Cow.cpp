#include "Cow.h"

Cow::Cow(NumberBoard* theNumberBoard,sf::FloatRect gameArea, float speed)
	: Animal(theNumberBoard,gameArea, speed, 10, 30),
	lastCollidedPoo(nullptr), goal(0.f,0.f)
{
	
	this->setTexture("../Images/sprites/cow_2.png",12,8, 3,4);
	this->getAnimationHelper()->setRowAnimationInstruction(3,0,1,2,1);
	this->getAnimationHelper()->toggleReversePlayback();

	this->setSpriteScale(0.5f,0.5f);
	this->setDirectionToAorB(Direction::Left,Direction::Right);
	this->setPosition(gameArea.left + (gameArea.width / 10.f) * (rand() % (9-1) + 1),
		(gameArea.height/ 10.f) * (rand() % (9 - 1) + 1));

	this->sound_moo[0].loadFromFile("../Sounds/moo_1.wav");	
	this->sound_moo[1].loadFromFile("../Sounds/moo_2.wav");
	this->sound_moo[2].loadFromFile("../Sounds/moo_3.wav");
	this->sound_moo[3].loadFromFile("../Sounds/moo_4.wav");
	play_moo.setLoop(false);
}

bool Cow::hasGoal()
{
	return goal != sf::Vector2f(0.f,0.f);
}

void Cow::relieaveWaste()
{
	this->setRelieavingWaste(true);	
	play_moo.setBuffer(sound_moo[rand() % 4]);
	play_moo.play();
}

void Cow::setDirectionToAorB(Direction alternativeOne, Direction alternativeTwo)
{
	bool selectDirection = (rand() % 2 == 0);
	if (selectDirection)
	{
		this->setCurrentDirection(alternativeOne);
	}
	else {
		this->setCurrentDirection(alternativeTwo);
	}
}

void Cow::move()
{
	if (hasGoal()) {
		
		float length = sqrt(goal.x * goal.x + goal.y * goal.y);
		sf::Vector2f normalized(goal.x / length, goal.y / length);
		this->moveSprite(normalized.x, normalized.y);
		if (normalized.x < -0.6 || normalized.x > 0.6) {
			if (normalized.x < 0) {
				this->getAnimationHelper()->animateLeft();
			}
			else {
				this->getAnimationHelper()->animateRight();
			}
		}
		else if (normalized.y < 0) {
			this->getAnimationHelper()->animateUp();
		}
		else if (normalized.y > 0) {
			this->getAnimationHelper()->animateDown();
		}
	}
	else {
		if (!this->isRelieavingWaste()) {

			//sf::Vector2f dirToMove(0.f,0.f); 
			
			this->moveSprite(dirToMove.x, dirToMove.y);

			Poo* collidedPoo = theNumberBoard->collidedWithPoo(*this);
			if (collidedPoo && lastCollidedPoo != collidedPoo) {
				
				if (this->getCurrentDirection() == Direction::Left)
				{
					setDirectionToAorB(Direction::Up, Direction::Down);
				}
				else if (this->getCurrentDirection() == Direction::Up)
				{
					setDirectionToAorB(Direction::Right, Direction::Left);
				}
				else if (this->getCurrentDirection() == Direction::Right)
				{
					setDirectionToAorB(Direction::Down, Direction::Up);
				}
				else if (this->getCurrentDirection() == Direction::Down)
				{
					setDirectionToAorB(Direction::Left, Direction::Right);
				}

				lastCollidedPoo = collidedPoo;
			}

			float padding = 30.f;

			if (getCurrentDirection() == Direction::Left) {

				if (this->getGameArea().left < this->getBounds().left) {

					this->getAnimationHelper()->animateLeft();
					dirToMove.x = LEFT; 
					dirToMove.y = 0.f;
					//this->moveSprite(LEFT, 0.f);
				}
				else {
					this->setCurrentDirection(Direction::Up);
				}
			}
			else if (getCurrentDirection() == Direction::Right) {
				if (this->getGameArea().left + this->getGameArea().width > this->getBounds().left + this->getBounds().width) {

					this->getAnimationHelper()->animateRight();
					dirToMove.x = RIGHT;
					dirToMove.y = 0.f;
					//this->moveSprite(RIGHT, 0.f);
				}
				else {
					this->setCurrentDirection(Direction::Down);
				}
			}
			else if (getCurrentDirection() == Direction::Up) {
				if (this->getGameArea().top - padding < this->getBounds().top) {

					this->getAnimationHelper()->animateUp();
					dirToMove.x = 0.f;
					dirToMove.y = UP;
					//this->moveSprite(0.f, UP);
				}
				else {
					this->setCurrentDirection(Direction::Right);
				}
			}
			else if (getCurrentDirection() == Direction::Down) {
				if (this->getGameArea().top + this->getGameArea().height - padding > this->getBounds().top + this->getBounds().height) {

					this->getAnimationHelper()->animateDown();
					dirToMove.x = 0.f;
					dirToMove.y = DOWN;
					//this->moveSprite(0.f, DOWN);
				}
				else {
					this->setCurrentDirection(Direction::Left);
				}
			}					

		}
		else {

			if (getCrapTimeCount() == 0) {
				setRelieavingWaste(false);
				crapOnTile();		
				
			}
		}

		if (getCrapIntervalCount() == 0) {
			this->getAnimationHelper()->animateIdle();
			//setRelieavingWaste(true);
			relieaveWaste();
			resetCrapTimeInterval();	
			play_moo.setBuffer(sound_moo[rand() % 4]);			
			play_moo.play();
			
		}
	}
	

}

void Cow::setGoal(sf::Vector2f pos)
{
	this->goal = pos;
}

void Cow::crapOnTile()
{
	
	sf::Vector2f posCowsButt;
	
	if (getAnimationHelper()->isCurrentDirectionDown()) {
		posCowsButt.x = this->getBounds().left + (this->getBounds().width / 4.f);
		posCowsButt.y = this->getBounds().top;
	}
	else if (getAnimationHelper()->isCurrentDirectionUp()) {
		posCowsButt.x = this->getBounds().left + (this->getBounds().width / 4.f);
		posCowsButt.y = this->getBounds().top + (this->getBounds().height / 4.f) * 3;
	}
	else if (getAnimationHelper()->isCurrentDirectionLeft()) {
		posCowsButt.x = this->getBounds().left + (this->getBounds().width / 4.f) * 3;
		posCowsButt.y = this->getBounds().top + (this->getBounds().height / 2.f) ;
	}
	else if (getAnimationHelper()->isCurrentDirectionRight()) {
		
		posCowsButt.x = this->getBounds().left - (this->getBounds().width / 4.f);
		posCowsButt.y = this->getBounds().top + (this->getBounds().height / 2.f) ;
	
	}
	Poo* poo = new Poo(posCowsButt);
	this->theNumberBoard->recievePoo(poo);
	this->theNumberBoard->markTileAsCrapped(poo->getBounds());
}
