#pragma once
#include "Entity.h"

class Player;
class Item : public Entity {

private:
	bool shouldTerminate;
public:
	Item(float speed);
	bool isTerminated();
	void terminate();

	virtual void use(Player* playerPtr) = 0;
	virtual void collided(Entity* collidedWith) = 0;


};
