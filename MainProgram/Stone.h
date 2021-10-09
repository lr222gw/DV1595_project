#pragma once
#include "Item.h"
#include "Cow.h"

class Game;
enum class Status {Held, Thrown, Collided, Landed};
class Stone : public Item {
	// Inherited via Item
private:
	Status status;
	sf::Vector2f direction;
	void setDirection(sf::Vector2f direction);
	Game* gamePtr;
	int timeCount; 	
protected:
	// Inherited via Item
	virtual void resetItemSpecifics() override;
public:
	Stone(Game* gamePtr);
	~Stone();
	virtual std::string present() override;
	virtual bool use(Player* playerPtr) override;
	virtual void collided(Entity* collidedWith) override;
	void move() override;

	
};
