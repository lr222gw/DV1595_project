#pragma once
#include"GameState.h"

class Menu :public GameState
{
private:
	static const int NR_OF_ALT = 2;
	static const int PLAY = 0;
	static const int EXIT = 1;

	sf::Text alternatives[NR_OF_ALT];
	sf::Font font;

	int prvSelected;
	int selected; 
	bool done;

	void moveUp();
	void moveDown();


public:
	Menu();
	virtual ~Menu();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};
