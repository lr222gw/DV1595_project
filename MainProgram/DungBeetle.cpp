#include "DungBeetle.h"
#include "Game.h"

DungBeetle::DungBeetle(Game* gamePtr)
	:Item(3, 5), gamePtr(gamePtr)
{
    this->setTexture("../Images/sprites/dungbeetle.png", 4, 2, 4, 2);    
    this->getAnimationHelper()->setRowAnimationInstruction(0, 0, 0, 1, 1);
    this->getAnimationHelper()->animateIdle();
}

void DungBeetle::move()
{
}

std::string DungBeetle::present()
{
    return "Dung beetle";
}

bool DungBeetle::use(Player* playerPtr)
{
    return true;
}

void DungBeetle::collided(Entity* collidedWith)
{
    auto poo = dynamic_cast<Poo*>(collidedWith);
    if (poo) {
        
        int r = 34;

    }
}
