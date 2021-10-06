#pragma once
#include "Item.h"

class Game;
class DungBeetle : public Item {
	static const int LEFT  = -1;
	static const int RIGHT = -1;
private:
	Game* gamePtr;
	int direction;
public:
	DungBeetle(Game* gamePtr);

	// Inherited via Item
	virtual void move() override;
	virtual std::string present() override;
	virtual bool use(Player* playerPtr) override;
	virtual void collided(Entity* collidedWith) override;
};
