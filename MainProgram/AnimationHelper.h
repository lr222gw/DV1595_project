#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class AnimationHelper {
private:
	static const int DOWN_ROW	=  0;
	static const int UP_ROW		=  1;
	static const int LEFT_ROW	=  2;
	static const int RIGHT_ROW	=  3;

	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::IntRect intRect;

	int lastRow;

	//We've hardcoded 60 as our fps... thus 30 = 0.5sec, 60 = 1sec ...
	int timeCounter;	//increases each tick
	int updateTime;		//How many ticks before we change image
	void moveIntRectAtUpdateTime();
public:
	AnimationHelper(sf::Texture &texture, sf::Sprite &sprite, int nrOfColumns, int nrOfRows);

	void update();

};