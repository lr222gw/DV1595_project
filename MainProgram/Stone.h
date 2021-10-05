#pragma once
#include "Item.h"
#include "Cow.h"

enum class Status {Held, Thrown, Collided, Landed};
class Stone : public Item {
	// Inherited via Item
private:
	Status status;
	sf::Vector2f direction;
	void setDirection(sf::Vector2f direction);

	int timeCount; 	

public:
	Stone();
	virtual std::string present() override;
	virtual void use(Player* playerPtr) override;
	virtual void collided(Entity* collidedWith) override;
	void move() override;
};
