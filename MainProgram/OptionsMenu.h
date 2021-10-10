#pragma once
#include "GameState.h"
#include "ControllerConfigurator.h"

class OptionsMenu : public GameState{

private:
	static const int NR_OF_ALT = 15;
	static const int DONE = 0;
	static const int PLAYER_ONE_LEFT	= 1;	
	static const int PLAYER_ONE_RIGHT	= 2;	
	static const int PLAYER_ONE_UP		= 3;	
	static const int PLAYER_ONE_DOWN	= 4;	
	static const int PLAYER_ONE_ACTION	= 5;	
	static const int PLAYER_ONE_BUY		= 6;	
	static const int PLAYER_ONE_BINGO	= 7;	
	static const int PLAYER_TWO_LEFT	= 8;	
	static const int PLAYER_TWO_RIGHT	= 9;	
	static const int PLAYER_TWO_UP		= 10;	
	static const int PLAYER_TWO_DOWN	= 11;	
	static const int PLAYER_TWO_ACTION	= 12;	
	static const int PLAYER_TWO_BUY		= 13;	
	static const int PLAYER_TWO_BINGO	= 14;	

	sf::Text Presentation;
	sf::Text alternatives[NR_OF_ALT];
	sf::Font font;

	int prvSelected;
	int selected;
	bool done;

	ControllerConfigurator conf;

	void moveUp();
	void moveDown();

public:
	OptionsMenu();
	virtual ~OptionsMenu();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};