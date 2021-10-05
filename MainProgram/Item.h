#pragma once
#include "Entity.h"

class Player;
class Item : public Entity {

private:
	bool shouldTerminate;
	int price;
public:
	Item(float speed, int price);
	bool isTerminated();
	void terminate();
	int getPrice() const;

	virtual std::string present() = 0;
	virtual void use(Player* playerPtr) = 0;
	virtual void collided(Entity* collidedWith) = 0;


};
