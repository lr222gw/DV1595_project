#include "ControllerConfigurator.h"

void ControllerConfigurator::createDefaultConfFile()
{
	//Create file
	std::ofstream file(configFilePath, std::ios::beg);
	file.close();
	//Default Settings
	appendInputPair(Actions::P1_Left,	sf::Keyboard::Key::A);
	appendInputPair(Actions::P1_Right,	sf::Keyboard::Key::D);
	appendInputPair(Actions::P1_Up,		sf::Keyboard::Key::W);
	appendInputPair(Actions::P1_Down,	sf::Keyboard::Key::S);
	appendInputPair(Actions::P1_Action, sf::Keyboard::Key::Space);
	appendInputPair(Actions::P1_Bingo,	sf::Keyboard::Key::C);
	appendInputPair(Actions::P1_Buy,	sf::Keyboard::Key::Q);
	appendInputPair(Actions::P2_Left,	sf::Keyboard::Key::Numpad4);
	appendInputPair(Actions::P2_Right,	sf::Keyboard::Key::Numpad6);
	appendInputPair(Actions::P2_Up,		sf::Keyboard::Key::Numpad8);
	appendInputPair(Actions::P2_Down,	sf::Keyboard::Key::Numpad5);
	appendInputPair(Actions::P2_Action, sf::Keyboard::Key::Enter);
	appendInputPair(Actions::P2_Bingo,	sf::Keyboard::Key::Numpad3);
	appendInputPair(Actions::P2_Buy,	sf::Keyboard::Key::Numpad7);
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

		if (iterationCounter != nrOfPairs) {
			assert(true && "The config file is invalid...");
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

std::string ControllerConfigurator::actionsEnumToString(Actions action)
{
	std::string toRet;
	switch (action) {
		case	Actions::P1_Left	  :
			toRet = "PlayerOne Left";
			break;
		case	Actions::P1_Right	  :
			toRet = "PlayerOne Right";
			break;
		case	Actions::P1_Up		  :
			toRet = "PlayerOne Up";
			break;
		case	Actions::P1_Down	  :
			toRet = "PlayerOne Down";
			break;
		case	Actions::P1_Action	  :
			toRet = "PlayerOne Action";
			break;
		case	Actions::P1_Bingo	  :
			toRet = "PlayerOne Bingo";
			break;
		case	Actions::P1_Buy		  :
			toRet = "PlayerOne Buy";
			break;
		case	Actions::P2_Left	  :
			toRet = "PlayerTwo Left";
			break;
		case	Actions::P2_Right	  :
			toRet = "PlayerTwo Right";
			break;
		case	Actions::P2_Up		  :
			toRet = "PlayerTwo Up";
			break;
		case	Actions::P2_Down	  :
			toRet = "PlayerTwo Down";
			break;
		case	Actions::P2_Action	  :
			toRet = "PlayerTwo Action";
			break;
		case	Actions::P2_Bingo	  :
			toRet = "PlayerTwo Bingo";
			break;
		case	Actions::P2_Buy		  :
			toRet = "PlayerTwo Buy";
			break;
		default:
			toRet = "Not A Actions Enum";

	}
	return toRet;
}



void ControllerConfigurator::setInputPair(Actions action, sf::Keyboard::Key inputKey)
{

	for (int i = 0; i < nrOfPairs; i++) {
		if (action == inputPairs[i].action) {
			inputPairs[i].key = inputKey;
		}
	}

	std::ofstream file(configFilePath, std::ios::beg);	

	if(file.is_open()) {
		for (int i = 0; i < nrOfPairs; i++) {

			file << (int)inputPairs[i].action << " " << (int)inputPairs[i].key << std::endl;
		}
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
