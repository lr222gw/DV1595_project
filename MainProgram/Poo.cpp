#include "Poo.h"
Poo::Poo(sf::Vector2f position)
{
	pooShape.setSize(sf::Vector2f(30,30));
	pooShape.setFillColor(sf::Color(120,100,20,200));
	pooShape.setPosition(position);
}

sf::FloatRect Poo::getBounds()
{
	return pooShape.getGlobalBounds();
}

void Poo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->pooShape);
}
