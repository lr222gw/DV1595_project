#include "Wheat.h"
#include "Player.h"
#include "Game.h"
Wheat::Wheat(Game* gamePtr)
    :Item(0, 40, .30f, .20f), status(Status::Held), gamePtr(gamePtr)
{
    this->setTexture("../Images/sprites/wheat.png", 1, 1, 1, 1);        
    this->getAnimationHelper()->setRowAnimationInstruction(0,0,0,0,0);    
    this->getAnimationHelper()->animateDown();
    
    eatingSound.loadFromFile("../Sounds/eat.wav");
    soundPlayer.setBuffer(eatingSound);

}

void Wheat::move()
{
    // Not needed here...
}

std::string Wheat::getName()
{
    return "Wheat";
}

bool Wheat::use(Player* playerPtr)
{
    this->goToCow = this->gamePtr->cowGoTo(
        sf::Vector2f(
            this->getBounds().left + this->getBounds().width / 2.f,
            this->getBounds().top + this->getBounds().height / 2.f
        )        
    );
    if (this->goToCow) {

        status = Status::Dropped;
    }

    return status == Status::Dropped;
}

void Wheat::collided(Entity* collidedWith)
{
    if (status == Status::Dropped) {
        
        auto cow = dynamic_cast<Cow*>(collidedWith);
        if (cow) {
            soundPlayer.play();

            this->setPosition(-100.f, -100.f);
            status = Status::Collided;
            this->terminate();

            cow->setRelieavingWaste(true);
           
            cow->setGoal(sf::Vector2f(0.f, 0.f)); // TODO: This should cause cow to go back to plane
            this->goToCow-> setGoal(sf::Vector2f(0.f, 0.f));
        }
    }
}

void Wheat::resetItemSpecifics()
{
    this->status = Status::Held;
}
