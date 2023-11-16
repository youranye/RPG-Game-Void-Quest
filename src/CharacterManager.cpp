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

	//Prompt Religion if needed
	Religion religion = FORGE;
	if (species != HUMAN)
	{
		if (species == DWARF)
		{
			//no prompt religion is FORGE
			religion = FORGE;
		}
		else if (species == ELF && class_type != PALADIN) //ELF ROGUE OR WARLOCK
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
		else if(class_type != PALADIN) //TABAXI or Goblin ROGUE OR WARLOCK
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
		if (class_type != PALADIN)
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
	return new Player(); //returning empty player for now
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