#pragma once
#include "Animal.h"


class Cow : public Animal {
private:

public:
	Cow(NumberBoard* theNumberBoard, sf::FloatRect gameArea, float speed);

	// Inherited via Animal
	virtual void move() override;
	void crapOnTile() override;
};
