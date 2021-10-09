#include "DungBeetle.h"
#include "Game.h"

DungBeetle::DungBeetle(Game* gamePtr)
	:Item(3, 5, 1.5f, 0.5f), gamePtr(gamePtr), status(Status::Held)
{
    this->setTexture("../Images/sprites/dungbeetle.png", 4, 2, 4, 2);    
    this->getAnimationHelper()->setRowAnimationInstruction(0, 0, 0, 1, 1);
    this->getAnimationHelper()->animateIdle();
}

void DungBeetle::move()
{
    if (this->status == Status::Dropped) {
        this->moveSprite(direction, 0.f);
        if (gamePtr->isOutSideGameArea(this->getBounds())) {
            this->terminate();
            this->status = Status::Done;
        }
    }
}

std::string DungBeetle::present()
{
    return "Dung beetle";
}

bool DungBeetle::use(Player* playerPtr)
{
    this->status    = Status::Dropped;

    if (playerPtr->getDirection().x == 0) {               
        this->direction = playerPtr->getDirection().y;                
    }
    else {
        this->direction = playerPtr->getDirection().x;
    }

    if (this->direction == 1) 
    {
        this->getAnimationHelper()->animateRight();
    }
    else 
    {
        this->getAnimationHelper()->animateLeft();
    }
    return true;
}

void DungBeetle::collided(Entity* collidedWith)
{
    Poo* poo = dynamic_cast<Poo*>(collidedWith);
    if (status == Status::Dropped) {
        if (poo) {

            this->gamePtr->unmarkTileAsCrapped_forwarded(poo->getBounds());
            poo->setPosition(-100.f, -100.f);
        }
        else if (Cow* cow = dynamic_cast<Cow*>(collidedWith)) {
            this->direction *= -1;

            this->direction == 1 ? this->getAnimationHelper()->animateRight() : this->getAnimationHelper()->animateLeft();
        }
    }
}
