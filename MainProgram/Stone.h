#pragma once
#include "Item.h"
#include "Cow.h"
#include <SFML/Audio.hpp>

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

	sf::SoundBuffer throwingSound;
	sf::SoundBuffer hitSound;
	sf::Sound soundPlayer;

protected:
	// Inherited via Item
	virtual void resetItemSpecifics() override;
public:
	Stone(Game* gamePtr);
	~Stone();
	virtual std::string getName() override;
	virtual bool use(Player* playerPtr) override;
	virtual void collided(Entity* collidedWith) override;
	void move() override;

	
};
