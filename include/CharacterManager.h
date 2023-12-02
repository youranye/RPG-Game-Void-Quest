#pragma once
#include "Character.h"
#include "Player.h"
#include "IOManager.h"
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>


class CharacterManager
{
protected:
	vector<Character> characters;
	Player* player;
	IOManager& ioManager;
	// Create a character according to the user's choices.
	Player* createPlayer();
	void addScriptedCharacters();
public:
	// Initialize enemy's and NPC's and put them in the characters vector.
	CharacterManager(IOManager& ioManager);

	// Initialize the player character.
	virtual void initialize();

	virtual ~CharacterManager();

	// Finds and returns the character whose name matches the parameter. Return nullCharacter if not found.
	Character& getCharacter(std::string);

	// Returns a pointer to the player character.
	Player* getPlayer();
};