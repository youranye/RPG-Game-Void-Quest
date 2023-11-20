#include "CharacterManager.h"

//create Player character
Player* CharacterManager::createPlayer()
{
	std::stringstream ss;
	IOManager iomanager(cin,cout);
	int choice = 0;

	ss << "Create your character!\n";

	//Prompt Species
	SpeciesType species = HUMAN;
	ss << "Choose your species. \n\t a. Human \n\t b. Elf \n\t c. Dwarf"
	   << "\n\t d. Goblin \n\t e. Tabaxi\n";
	//iomanager.write(ss.str());
	//choice = iomanager.readOption(5);
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
		//iomanager.write(ss.str());
		//choice = iomanager.readOption(2);
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
		//iomanager.write(ss.str());
		//choice = iomanager.readOption(3);
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

	string name = " ";
	//prompt and get name
	ss << "Name your character: ";
	//iomanager.write(ss.str());
	//TODO: add read function to IOManager and use to get string
	cin >> name;

	//Prompt Religion if needed
	Religion religion = FORGE;
	if (species != HUMAN)
	{
		if (species == DWARF)
		{
			//no prompt religion is FORGE
			religion = FORGE;
		}
		else if (species == ELF && type != PALADIN) //ELF ROGUE OR WARLOCK
		{
			//prompt shadow, silver
			//prompt vague question trickery or wealth depending on answer pick religion
			bool response = false; //temp placeholder
			if (response)
			{
				religion = SHADOW;
			}
			else
			{
				religion = SILVER;
			}
		}
		else if (species == ELF)
		{
			//no prompt, religion is SILVER
			religion = SILVER;
		}
		else if(type != PALADIN) //TABAXI or Goblin ROGUE OR WARLOCK
		{
			//no prompt religion is SHADOW
			religion = SHADOW;
		}
		else
		{
			//no prompt religion is NOTHING
			religion = NOTHING;
		}
	}
	else //is human
	{
		if (type != PALADIN)
		{
			//prompt traveler, shadow
			// prompt pick background traveler, or smuggler
			//traveler is follower of Traveler
			//smuggler is follower of SHADOW
			bool response = false; //temp placeholder
			if (response)
			{
				religion = TRAVELER;
			}
			else
			{
				religion = SHADOW;
			}
		}
		else
		{
			//no prompt religion is traveler
			religion = TRAVELER;
		}
	}

	//create player
	return new Player(name, species, PLAYER, type, religion, 25,25); //returning empty player for now
}

CharacterManager::CharacterManager()
{
	//insert enemy characters into the Character array & npcs when Enemy and NPC characters are finished

	player = nullptr; //initialize player pointer to nullpointer
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