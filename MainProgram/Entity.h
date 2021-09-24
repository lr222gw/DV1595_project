#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AnimationHelper.h"

class Entity : public sf::Drawable {
private:

	sf::Sprite sprite;
	sf::Texture texture;
	 
	AnimationHelper* animationHelper;

	float speed;	
	 
protected:

public:
	Entity(std::string textureFile, int nrOfColumns, int nrOfRows, float speed);
	virtual ~Entity();

	void setPosition(float x, float y);
	void setTexture(std::string texturePath);

	void moveSprite(float x, float y);

	virtual void move() = 0;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};