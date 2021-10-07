#pragma once
#include "Item.h"
#include "Poo.h"

class Game;
class DungBeetle : public Item {
	enum class Status {Held, Dropped, Done};
	static const int LEFT  = -1;
	static const int RIGHT = -1;
private:
	Game* gamePtr;
	int direction;
	Status status;
public:
	DungBeetle(Game* gamePtr);

	// Inherited via Item
	virtual void move() override;
	virtual std::string present() override;
	virtual bool use(Player* playerPtr) override;
	virtual void collided(Entity* collidedWith) override;
};
