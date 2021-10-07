#pragma once
#include "Animal.h"


class Cow : public Animal {
private:
	Poo* lastCollidedPoo;
	void setDirectionToAorB(Direction alternativeOne, Direction alternativeTwo); 
	sf::Vector2f goal;

	sf::Vector2f dirToMove ;
	
public:
	bool hasGoal();
	void setGoal(sf::Vector2f pos);
	Cow(NumberBoard* theNumberBoard, sf::FloatRect gameArea, float speed);

	// Inherited via Animal
	virtual void move() override;
	void crapOnTile() override;
};
