#include "ControllerConfigurator.h"

void ControllerConfigurator::createDefaultConfFile()
{
	//Create file
	std::ofstream file(configFilePath, std::ios::beg);
	file.close();
	//Default Settings
	appendInputPair(Actions::P1_Left, sf::Keyboard::Key::A);
	appendInputPair(Actions::P1_Right, sf::Keyboard::Key::D);
	appendInputPair(Actions::P1_Up, sf::Keyboard::Key::W);
	appendInputPair(Actions::P1_Down, sf::Keyboard::Key::S);
	appendInputPair(Actions::P1_Action, sf::Keyboard::Key::Space);
	appendInputPair(Actions::P1_Bingo, sf::Keyboard::Key::C);
	appendInputPair(Actions::P1_Buy, sf::Keyboard::Key::Q);
	appendInputPair(Actions::P2_Left, sf::Keyboard::Key::Numpad4);
	appendInputPair(Actions::P2_Right, sf::Keyboard::Key::Numpad6);
	appendInputPair(Actions::P2_Up, sf::Keyboard::Key::Numpad8);
	appendInputPair(Actions::P2_Down, sf::Keyboard::Key::Numpad5);
	appendInputPair(Actions::P2_Action, sf::Keyboard::Key::Enter);
	appendInputPair(Actions::P2_Bingo, sf::Keyboard::Key::Numpad3);
	appendInputPair(Actions::P2_Buy, sf::Keyboard::Key::Numpad7);
}
void ControllerConfigurator::appendInputPair(Actions action, sf::Keyboard::Key inputKey)
{
	std::ofstream file(configFilePath, std::ios::app);

	if (file.is_open()) {
		file << (int)action << " " << (int)inputKey << std::endl;
	}

	file.close();
}

std::ifstream* ControllerConfigurator::createOrOpenFile(std::string path, std::ios_base::openmode mode)
{
	std::ifstream *file = new std::ifstream(configFilePath, std::ios::beg);
	if (!file->is_open()) {
		createDefaultConfFile(); 
	}
	return file;
}

void ControllerConfigurator::loadConfig()
{
	
	std::ifstream* file = createOrOpenFile(configFilePath, std::ios::beg);
	
	
	if (file->is_open()) {
		
		std::string input;
		int iterationCounter = 0;

		while (std::getline(*file, input)) {
			
			std::string delimiter = " ";

			Actions currentAction = (Actions)std::stoi((input.substr(0, input.find(delimiter))));
			sf::Keyboard::Key currentKey = (sf::Keyboard::Key)std::stoi(input.substr(input.find(delimiter)));

			inputPairs[iterationCounter].action = currentAction;
			inputPairs[iterationCounter].key = currentKey;

			iterationCounter++;
		}		

	}

	file->close();
	delete file;
}

ControllerConfigurator::ControllerConfigurator()
{	
	configFilePath = "controllerConf.txt";
	loadConfig();


}



void ControllerConfigurator::setInputPair(Actions action, sf::Keyboard::Key inputKey)
{

	std::ofstream file(configFilePath, std::ios::app);
	
	if(file.is_open()) {
		file << (int)action << " " << (int)inputKey << std::endl;
	}

	file.close();

}

sf::Keyboard::Key ControllerConfigurator::getActionKey(Actions action)
{
	sf::Keyboard::Key keyForAction = sf::Keyboard::Unknown;
	
	for (int i = 0; i < nrOfPairs && keyForAction == sf::Keyboard::Unknown;i++) {
		if (action == inputPairs[i].action) {
			keyForAction = inputPairs[i].key;
		}
	}

	return keyForAction;
}
