#pragma once
#include <SFML/Window.hpp> //Contains sf::Keyboard...
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>

enum class Actions{
	P1_Left, P1_Right, P1_Up, P1_Down,	//P1 Movement
	P1_Action, P1_Bingo, P1_Buy,		//P1 Actions

	P2_Left, P2_Right, P2_Up, P2_Down,	//P2 Movement
	P2_Action, P2_Bingo, P2_Buy,		//P2 Actions

	_END
};

struct InputPair {	
	Actions action;
	sf::Keyboard::Key key;	
};

class ControllerConfigurator {

private:
	std::string configFilePath;
	void createDefaultConfFile();
	void appendInputPair(Actions action, sf::Keyboard::Key inputKey);
	std::ifstream* createOrOpenFile(std::string path, std::ios_base::openmode mode);	
	void saveConfig();
	static const int nrOfPairs = 14;
	InputPair inputPairs[nrOfPairs];

public:
	ControllerConfigurator();
	void loadConfig();

	std::string actionsEnumToString(Actions action);

	void setInputPair(Actions action, sf::Keyboard::Key inputKey);
	sf::Keyboard::Key getActionKey(Actions action);
};
