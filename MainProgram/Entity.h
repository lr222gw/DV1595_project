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
	AnimationHelper* getAnimationHelper();
	static const int RIGHT	= 1;
	static const int LEFT	= -1;
	static const int DOWN	= 1;
	static const int UP		= -1;
public:
	Entity(float speed);
	virtual ~Entity();

	void setPosition(float x, float y);
	void setTexture(std::string texturePath, int nrOfColumns, int nrOfRows, int columnsSubset, int rowsSubset);
	void moveSprite(float x, float y);
	void setSpriteScale(float x, float y);

	sf::FloatRect getBounds();
	bool hitBy(const sf::FloatRect &ref);

	void update();


	virtual void move() = 0;
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};