#pragma once
#include "Item.h"
#include "Cow.h"

class Game;
class Wheat : public Item {
enum class Status { Held, Collided, Dropped };
private:
	Status status;
	Game* gamePtr;
	Cow* goToCow;
protected:
	// Inherited via Item
	virtual void resetItemSpecifics() override;
public:
	Wheat(Game* gamePtr);
	// Inherited via Item
	virtual void move() override;
	virtual std::string present() override;
	virtual bool use(Player* playerPtr) override;
	virtual void collided(Entity* collidedWith) override;

};