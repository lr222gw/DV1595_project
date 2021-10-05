#include "Stone.h"
#include "Player.h"

Stone::Stone()
	: Item(8, 30), status(Status::Held)
{
	this->setTexture("../Images/sprites/stone.png", 8, 8, 8, 8);
	this->setSpriteScale(0.10f,0.10f);
	this->getAnimationHelper()->toggleReversePlayback();
}

std::string Stone::present()
{
	return "Stone";
}

void Stone::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

void Stone::use(Player* playerPtr)
{
		
	this->getAnimationHelper()->animateDown();
	this->setDirection(playerPtr->getDirection());
	status = Status::Thrown;
	
}

void Stone::collided(Entity* collidedWith)
{
	if (status == Status::Thrown) {
		this->moveSprite(0.f, 1.f);
		status = Status::Collided;
		timeCount = 0;
		
		auto cow = dynamic_cast<Cow*>(collidedWith);
		if (cow) {
			cow->setRelieavingWaste(true);
			//cow->crapOnTile();
		}
	}
}

void Stone::move()
{
	timeCount = (timeCount + 1) % (15); // 
	
	if (status == Status::Held) {
		
	}
	else if (status == Status::Thrown) {
		this->moveSprite(direction.x, direction.y);
	}
	else if (status == Status::Collided) {
		this->moveSprite(0.f, 0.55f);
		if (timeCount == 0) {
			status = Status::Landed;
			this->getAnimationHelper()->animateIdle();
		}
	}
	else if (status == Status::Landed) {
				
		if (timeCount == 0) {			
			this->setPosition(-100.f, -100.f);
		}
	}
	
}
