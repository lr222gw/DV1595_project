#pragma once
#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable {
private:

	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect intRect;

	float speed;
	int timeCounter;
	int updateTime;
	 
protected:

public:

	//virtual ~Entity();

	void setPosition(float x, float y);
	void setTexture(std::string texturePath);

	void moveSprite(float x, float y);

	virtual void move() = 0;



	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};