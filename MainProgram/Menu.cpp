#include "Menu.h"
#include <iostream>

void Menu::moveUp()
{
	/*

	uppdatera selected om möjligt och byt färg så att aktivt menyalterantiv är rött (annars gult)
	
	*/
	prvSelected = selected;
	selected = (selected - 1) % (NR_OF_ALT);
	
	/// If negative, then change to last meny alternative
	if (selected == -1) {
		selected = NR_OF_ALT - 1;
	}

	alternatives[selected].setFillColor(sf::Color::Red);
	alternatives[selected].setCharacterSize(30);	

	alternatives[prvSelected].setFillColor(sf::Color::Yellow);
	alternatives[prvSelected].setCharacterSize(30);
	
	
}

void Menu::moveDown()
{
	/*
	
	uppdatera selected om möjligt och byt färg  så att aktivt menyalterantiv är rött (annars gult)
	
	*/

	prvSelected = selected;
	selected = (selected + 1) % (NR_OF_ALT);

	alternatives[selected].setFillColor(sf::Color::Red);
	alternatives[selected].setCharacterSize(30);

	alternatives[prvSelected].setFillColor(sf::Color::Yellow);
	alternatives[prvSelected].setCharacterSize(30);
}

Menu::Menu()
	:GameState("Menu")
{
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	alternatives[PLAY].setFont(font);
	alternatives[PLAY].setFillColor(sf::Color::Red);
	alternatives[PLAY].setCharacterSize(30);
	alternatives[PLAY].setString("Play");
	alternatives[PLAY].setPosition(200.f, 200.f);

	alternatives[EXIT].setFont(font);
	alternatives[EXIT].setFillColor(sf::Color::Yellow);
	alternatives[EXIT].setCharacterSize(30);
	alternatives[EXIT].setString("Exit");
	alternatives[EXIT].setPosition(200.f, 350.f);

	
	selected = 0;
	done = false;
}

Menu::~Menu()
{
}

State Menu::update()
{
	State finalState = State::NO_CHANGE;
	/*

	om ingen förändring har skett ska retur göras motsvarande ingen förändring och annars ska ett relevant State returneras

	*/

	if (done) {
		switch (selected) {
		case PLAY:
			finalState = State::PLAY;
			break;
		case EXIT:
			finalState = State::EXIT;
			break;
		} 

	}

	
	return finalState;
}

void Menu::render()
{
	window.clear();

	for (int i = 0; i < NR_OF_ALT; i++) {
		window.draw(alternatives[i]);
	}
	
	window.display();
}

void Menu::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		/*

		undersök och agera på tangetnedtryckningar (Up, Down, Return) där Return betyder att användaren bekräftar sitt val

		*/
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				
				moveDown();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				
				moveUp();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				done = true;
			}
		}
		
	}
}

