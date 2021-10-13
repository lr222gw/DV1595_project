#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class AnimationHelper {
private:
	int down_row; 
	int up_row; 
	int left_row; 
	int right_row;
	int idle_column;

	bool reversePlayback;
	bool rightDir_playback;

	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::IntRect intRect;

	int nrOfRows;
	int nrOfColumns;
	int columnsSubset;	// in case a row is used for several types of animation
	int rowsSubset;		// in case the spritesheet has several different sprites

	int lastRow;
	int animationDirection; 

	//We've hardcoded 60 as our fps... thus 30 = 0.5sec, 60 = 1sec ...
	int timeCounter;	//increases each tick
	int updateTime;		//How many ticks before we change image
	void moveIntRectAtUpdateTime();
public:
	AnimationHelper(sf::Sprite &sprite);

	void toggleReversePlayback();
	void setRowAnimationInstruction(int up, int down, int left, int right, int idle);
	void animateUp();
	void animateDown();
	void animateLeft();
	void animateRight();
	void animateIdle();

	bool isCurrentDirectionDown();
	bool isCurrentDirectionUp();
	bool isCurrentDirectionLeft();
	bool isCurrentDirectionRight();
	

	void setTexture(sf::Texture& texture, int nrOfColumns, int nrOfRows, int columnsSubset, int rowsSubset);

	void update();

};