#pragma once
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "IOManager.h"
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>


using namespace std;

class CharacterManager
{
	vector<Character> characters;
	Player* player;

	// Create a character according to the user's choices.
	Player* createPlayer();
public:
	// Initialize enemy's and NPC's and put them in the characters vector.
	CharacterManager();

	// Initialize the player character.
	void initialize();

	~CharacterManager();

	// Finds and returns the character whose name matches the parameter. Return nullCharacter if not found.
	Character& getCharacter(string);

	// Returns a pointer to the player character.
	Player* getPlayer();
};