#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class AnimationHelper {
private:
	int down_row; 
	int up_row; 
	int left_row; 
	int right_row;
	int idle_row;

	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::IntRect intRect;

	int lastRow;
	int animationDirection; 

	//We've hardcoded 60 as our fps... thus 30 = 0.5sec, 60 = 1sec ...
	int timeCounter;	//increases each tick
	int updateTime;		//How many ticks before we change image
	void moveIntRectAtUpdateTime();
public:
	AnimationHelper(sf::Texture &texture, sf::Sprite &sprite, int nrOfColumns, int nrOfRows);

	void setRowAnimationInstruction(int up, int down, int left, int right);
	void animateUp();
	void animateDown();
	void animateLeft();
	void animateRight();
	void animateIdle();

	void update();

};