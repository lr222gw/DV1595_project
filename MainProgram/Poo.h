#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Poo : public Entity{
private:
	sf::Time timeLeft;
public:

	Poo(sf::Vector2f position);

	// Inherited via Entity
	virtual void move() override;

};
