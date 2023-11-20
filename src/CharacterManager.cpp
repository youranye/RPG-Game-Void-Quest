#include "CharacterManager.h"
//will adjust prompts when IOManager is finished
Player* CharacterManager::create_player()
{
	//create Player character
	//prompt Species
	SpeciesType species = HUMAN;
	//HUMAN, ELF, DWARF, GOBLIN, TABAXI
	//get response

	//prompt Classes
	ClassType class_type = FORGED;
	if (species == DWARF)
	{
		//prompt Rogue, Forged
	}
	else
	{
		//prompt Rogue, Paladin, Warlock
	}

	string name = " ";
	//prompt and get name

	//create player
	return new Player(); //returning empty player for now
}

CharacterManager::CharacterManager()
{
	//insert enemy characters into the Character array
	characters.push_back(Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15));
	characters.push_back(Character("Barry the HobGoblin",GOBLIN,ENEMY,310,20,15,15));
	characters.push_back(Character("Barry the Orc",ORC,ENEMY,600,35,30,5));
	player = nullptr; //initialize player pointer to nullpointer
}

void CharacterManager::initialize()
{
	if(player == nullptr)
	{
		player = create_player(); //create player and set player pointer to player
	} else
	{
		//exception
		throw std::logic_error("Cannot call initialize more than once");
	}
}

CharacterManager::~CharacterManager()
{
	//properly delete and set player pointer
	delete player;
	player = nullptr;
}

Character& CharacterManager::get_character(string name)
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters.at(i).get_name() == name)
		{
			return characters.at(i);
		}
	}
	return nullCharacter;
}

Player* CharacterManager::get_player()
{
	return player;
}