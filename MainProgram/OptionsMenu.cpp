#include "OptionsMenu.h"

void OptionsMenu::moveUp()
{


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

void OptionsMenu::moveDown()
{

	prvSelected = selected;
	selected = (selected + 1) % (NR_OF_ALT);

	alternatives[selected].setFillColor(sf::Color::Red);
	alternatives[selected].setCharacterSize(30);

	alternatives[prvSelected].setFillColor(sf::Color::Yellow);
	alternatives[prvSelected].setCharacterSize(30);
}

OptionsMenu::OptionsMenu()
	:GameState("Options")
{
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	Presentation.setFont(font);
	Presentation.setFillColor(sf::Color::Magenta);
	Presentation.setCharacterSize(45);
	Presentation.setString("Input Options");	
	Presentation.setPosition(100.f, 50.f);

	alternatives[DONE].setFont(font);
	alternatives[DONE].setFillColor(sf::Color::Yellow);
	alternatives[DONE].setCharacterSize(30);
	alternatives[DONE].setString("Done");	
	alternatives[DONE].setPosition(100.f, (float)(window.getSize().y / 10) * 9);



	selected = 0;
	done = false;
}

OptionsMenu::~OptionsMenu()
{
}

State OptionsMenu::update()
{
	State finalState = State::NO_CHANGE;


	if (done) {
		switch (selected) {
		case DONE:
			finalState = State::MENU;
			break;
		}

	}


	return finalState;
}

void OptionsMenu::render()
{
	window.clear();
	window.draw(Presentation);
	for (int i = 0; i < NR_OF_ALT; i++)
	{
		window.draw(alternatives[i]);
	}
	window.display();
}

void OptionsMenu::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
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
