#include "Wheat.h"
#include "Player.h"
#include "Game.h"
Wheat::Wheat(Game* gamePtr)
    :Item(0, 5), status(Status::Held), gamePtr(gamePtr)
{
    this->setTexture("../Images/sprites/wheat.png", 1, 1, 1, 1);    
    this->setSpriteScale(.20f, .20f);
    this->getAnimationHelper()->setRowAnimationInstruction(0,0,0,0,0);    
    this->getAnimationHelper()->animateDown();
    
}

void Wheat::move()
{
}

std::string Wheat::present()
{
    return "Wheat";
}

bool Wheat::use(Player* playerPtr)
{
    this->gamePtr->cowGoTo(
        sf::Vector2f(
            this->getBounds().left + this->getBounds().width / 2.f,
            this->getBounds().top + this->getBounds().height / 2.f
        )        
    );
    status = Status::Dropped;

    return true;
}

void Wheat::collided(Entity* collidedWith)
{
    if (status == Status::Dropped) {
        this->moveSprite(0.f, 1.f);
        status = Status::Collided;        

        auto cow = dynamic_cast<Cow*>(collidedWith);
        if (cow) {
            cow->setRelieavingWaste(true);
           
            cow->setGoal(sf::Vector2f(0.f, 0.f)); // TODO: This should cause cow to go back to plane
            
        }
    }
}
