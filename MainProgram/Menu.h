#pragma once
#include"GameState.h"

class Menu :public GameState
{
private:
	static const int NR_OF_ALT = 3;
	static const int PLAY = 0;
	static const int OPTIONS = 1;
	static const int EXIT = 2;

	sf::Text alternatives[NR_OF_ALT];
	sf::Font font;

	int prvSelected;
	int selected; 
	bool done;

	void moveUp();
	void moveDown();


public:
	Menu(sf::RenderWindow* window);
	virtual ~Menu();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};
