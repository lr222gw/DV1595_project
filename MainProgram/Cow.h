#pragma once
#include "Animal.h"


class Cow : public Animal {
private:

public:
	Cow(sf::FloatRect gameArea, float speed);

	// Inherited via Animal
	virtual void move() override;
};
