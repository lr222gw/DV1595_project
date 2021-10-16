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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameState* current = nullptr;
	State currentState = State::NO_CHANGE;

	current = new Menu();
	currentState = State::MENU;

	while (currentState != State::EXIT)
	{
		current->handleEvents();
		currentState = current->update();
		
		if (currentState != State::NO_CHANGE)
		{

			switch (currentState)
			{
			case State::MENU:
				delete current;
				current = new Menu();
				break;
			case State::PLAY:
				delete current;
				current = new Game();
				break;
			case State::OPTIONS:
				delete current;
				current = new OptionsMenu();
				break;
			}
		}
		current->render();
	}

	delete current;
	getchar();
	return 0;
}