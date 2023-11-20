#include "CharacterManager.h"

//create Player character
Player* CharacterManager::createPlayer()
{
	std::stringstream ss;
	int choice = 0;

	ss << "Create your character!\n";

	//Prompt Species
	SpeciesType species = HUMAN;
	ss << "Choose your species. \n\t a. Human \n\t b. Elf \n\t c. Dwarf"
	   << "\n\t d. Goblin \n\t e. Tabaxi\n";
	ioManager.write(ss.str());
	choice = ioManager.readOption(5);
	switch (choice)
	{
		case 0:
			species = HUMAN;
			break;
		case 1:
			species = ELF;
			break;
		case 2:
			species = DWARF;
			break;
		case 3:
			species = GOBLIN;
			break;
		case 4:
			species = TABAXI;
			break;
	}

	// Prompt Classes
	ClassType type = ROGUE;
	if (species == DWARF)
	{
		//prompt Rogue, Forged
		ss << "Choose your class. \n\t a. Rogue: sly trickster with very good dexterity and aim \n\t"
		   << "b. Forged: mechanically enhanced dwarf with good attack and defense\n";
		ioManager.write(ss.str());
		choice = ioManager.readOption(2);
		switch(choice)
		{
			case 0:
				type = ROGUE;
				break;
			case 1:
				type = FORGED;
				break;
		}
	}
	else
	{
		//prompt Rogue, Paladin, Warlock
		ss << "Choose your class. \n\t a. Rogue: sly trickster with very good dexterity \n\t"
		   << "b. Paladin: shining knight with good defense"
		   << "c. Warlock: powerful spellcaster with good aim\n";
		ioManager.write(ss.str());
		choice = ioManager.readOption(3);
		switch(choice)
		{
			case 0:
				type = ROGUE;
				break;
			case 1:
				type = PALADIN;
				break;
			case 2:
				type = WARLOCK;
				break;
		}
	}

	std::string name = " ";
	//prompt and get name
	ss << "Name your character: ";
	ioManager.write(ss.str());
	//TODO: add read function to IOManager and use to get string
	//cin >> name;

	//create player
	//Player* newplayer = new Player();
	return new Player(name, species, type, 200, 100);
	//return newplayer;

}

CharacterManager::CharacterManager(IOManager& ioManager) : ioManager(ioManager), player(nullptr)
{
	//insert enemy characters into the Character array & npcs when Enemy and NPC characters are finished
	
}

void CharacterManager::initialize()
{
	if(player == nullptr)
	{
		player = createPlayer(); //create player and set player pointer to player
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

Character& CharacterManager::getCharacter(string name)
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters.at(i).getName() == name)
		{
			return characters.at(i);
		}
	}
	return nullCharacter;
}

Player* CharacterManager::getPlayer()
{
	return player;
}