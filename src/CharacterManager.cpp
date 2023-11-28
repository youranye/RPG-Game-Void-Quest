#include "CharacterManager.h"

CharacterManager::CharacterManager(IOManager& ioManager) : ioManager(ioManager), player(nullptr)
{
	//insert enemy characters into the Character array
	characters.push_back(Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15));
	characters.push_back(Character("Barry the HobGoblin",GOBLIN,ENEMY,310,20,15,15));
	characters.push_back(Character("Barry the Orc",ORC,ENEMY,600,35,30,5));	
	addScriptedCharacters();
}

void CharacterManager::addScriptedCharacters()
{
	characters.push_back(Character("The Dwarf Warrior",DWARF,ENEMY,100,15,10,10));
	characters.push_back(Character("The Goblin Warrior",GOBLIN,ENEMY,100,15,10,10));
	characters.push_back(Character("Rick The Janitor",HUMAN,BOSS,50,3,5,50,Ability("Sweep",ATTACK,"Swings his mop wildly around",NONE,200,18)));
	characters.push_back(Character("Grim the Orc",ORC,ENEMY,175,20,10,10));
	characters.push_back(Character("The Laughing Gobin",GOBLIN,BOSS,100,10,10,10,Ability("Laugh",DEBUFF,"Laughs histerically, and throws a flower shaped dagger that hits you in the chest",DEX,25,18)));
	characters.push_back(Character("The Dwarf",DWARF,ENEMY,600,1,30,1));
	characters.push_back(Character("Y.o.u",CHANGELING,BOSS,200,15,15,15,Ability("Charm Yourself",ATTACK,"Takes a step towards you and dissapears as you think to yourself that this thing looks familiar, you feel a sharp pain",NONE,125,18)));
	characters.push_back(Character("GrimGard The Goliath",GOLIATH,BOSS,600,30,25,10,Ability("Jump",DEBUFF,"runs and jumps towards you, causing the ground around you to shake violenty",DEX,75,18)));
	characters.push_back(Character("The Shapeless being",VOIDWALKER,BOSS,400,40,5,19,Ability("???",ATTACK,"spews forth a volly of spells at you",NONE,150,18)));
	characters.push_back(Character("The Silvery Figure",ELF,BOSS,200,25,15,20,Ability("Sneak Attack",ATTACK,"calls upon The power of Silverial, Shimmers Brightly for a second; and stabs you in the Back",NONE,200,18)));
	characters.push_back(Character("The Angry Gnome",GNOME,ENEMY,50,5,5,30,Ability("Ankle Biter",ATTACK,"runs at you and bites your ankles",NONE,200,18)));
	characters.push_back(Character("The Angry Gnome",GNOME,ENEMY,50,5,5,30,Ability("Ankle Biter",ATTACK,"runs at you and bites your ankles",NONE,200,18)));
	characters.push_back(Character("Gnome of the Forest",GNOME,ENEMY,50,5,5,30,Ability("Ankle Biter",ATTACK,"runs at you and bites your ankles",NONE,200,18)));
	characters.push_back(Character("The Forest Gnome",GNOME,ENEMY,50,7,5,25,Ability("Ankle Biter",ATTACK,"runs at you and bites your ankles",NONE,200,18)));
	characters.push_back(Character("The VoidWalker",VOIDWALKER,BOSS,1000,50,2,15,Ability("???",ATTACK,"spews forth a uncontrollable volly of spells at you",NONE,150,50)));
}

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
	ioManager.read(name);

	//create player
	Player* newPlayer = new Player(name, species, type, 200, 100);
	return newPlayer;
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

Character& CharacterManager::getCharacter(std::string name)
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