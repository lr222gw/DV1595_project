#pragma once
#include <SFML/Graphics.hpp>

class Poo : public sf::Drawable{
private:
	sf::RectangleShape pooShape;
	sf::Time timeLeft;
public:

	Poo(sf::Vector2f position);

	void moveShape();


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
