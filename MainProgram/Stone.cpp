#include "Stone.h"
#include "Player.h"
#include "Game.h"

Stone::Stone(Game* gamePtr)
	: Item(8, 5, .1f, .1f), status(Status::Held), gamePtr(gamePtr)
{
	static sf::Texture textur; 
	static sf::SoundBuffer hit;
	static sf::SoundBuffer throwed;
	if (textur.getSize().x == 0) {
		textur.loadFromFile("../Images/sprites/stone.png");
		throwed.loadFromFile("../Sounds/throwed.wav");
		hit.loadFromFile("../Sounds/hit_cow.wav");
	}
	
	this->setTexture(&textur, 8, 8, 8, 8);
	this->getAnimationHelper()->toggleReversePlayback();

	throwingSound = throwed;
	hitSound = hit;
	soundPlayer.setBuffer(throwingSound);
}

Stone::~Stone()
{
	int i = 0;
}

std::string Stone::getName()
{
	return "Stone";
}

void Stone::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

bool Stone::use(Player* playerPtr)
{
	soundPlayer.setBuffer(throwingSound);
	soundPlayer.play();
	this->getAnimationHelper()->animateDown();
	this->setDirection(playerPtr->getDirection());
	status = Status::Thrown;
	return true;
	
}

void Stone::collided(Entity* collidedWith)
{
	if (status == Status::Thrown) {
						
		auto cow = dynamic_cast<Cow*>(collidedWith);
		if (cow) {
			cow->relieaveWaste();
			this->moveSprite(0.f, 1.f);
			status = Status::Collided;
			timeCount = 0;
			soundPlayer.setBuffer(hitSound);
			soundPlayer.play();
		}
		else if (auto player = dynamic_cast<Player*>(collidedWith)) {
			if (player != getOwner()) {

				player->punish();
				status = Status::Collided;
				timeCount = 0;
				soundPlayer.setBuffer(hitSound);
				soundPlayer.play();
			}
		}
	}
}

void Stone::move()
{
	timeCount = (timeCount + 1) % (15); // 
	
	if (!gamePtr->isOutSideGameArea(this->getBounds()) ) {
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
				this->terminate();
			}
		}		
	}
	else {
		if (status == Status::Thrown) {
			this->terminate();
		}
	}
	
}

void Stone::resetItemSpecifics()
{
	status = Status::Held;
}
