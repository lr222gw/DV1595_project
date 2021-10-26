#include <SFML/Graphics.hpp>

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#endif
#include "Game.h"
#include "Menu.h"
#include "OptionsMenu.h"

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1200, 600), "CowBingo", sf::Style::Titlebar | sf::Style::Close);
	window->setSize(sf::Vector2u(1200,600));
	GameState* current = nullptr;
	State currentState = State::NO_CHANGE;

	current = new Menu(window);
	currentState = State::MENU;
	GameState* switched = nullptr;
	while (currentState != State::EXIT)
	{
		current->handleEvents();
		
		currentState = current->update();
		
		if (currentState != State::NO_CHANGE)
		{

			switch (currentState)
			{
			case State::MENU:
				switched = current;
				current = new Menu(window);
				break;
			case State::PLAY:
				switched = current;
				current = new Game(window);
				break;
			case State::OPTIONS:
				switched = current;
				current = new OptionsMenu(window);
				break;
			}

			if(switched){
				delete switched;
				switched = nullptr;
			}
		}
		current->render();
		
	}

	delete current;
	delete window;
	
	return 0;
}