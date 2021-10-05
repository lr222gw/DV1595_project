#pragma once
#include "Item.h"


class Game;
class Wheat : public Item {
enum class Status { Held, Collided, Dropped };
private:
	Status status;
	Game* gamePtr;
public:
	Wheat(Game* gamePtr);
	// Inherited via Item
	virtual void move() override;
	virtual std::string present() override;
	virtual bool use(Player* playerPtr) override;
	virtual void collided(Entity* collidedWith) override;
};