#pragma once
#include "Animal.h"
#include <SFML/Audio.hpp>

class Cow : public Animal {
private:
	Poo* lastCollidedPoo;
	void setDirectionToAorB(Direction alternativeOne, Direction alternativeTwo); 
	sf::Vector2f goal;

	sf::SoundBuffer sound_moo[4];		

	sf::Sound play_moo;

	sf::Vector2f dirToMove;
	
public:
	bool hasGoal();
	void setGoal(sf::Vector2f pos);
	Cow(NumberBoard* theNumberBoard, sf::FloatRect gameArea, float speed);

	void relieaveWaste(); 	

	// Inherited via Animal
	virtual void move() override;
	void crapOnTile() override;
};
