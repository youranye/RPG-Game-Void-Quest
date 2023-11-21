#pragma once
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "iomanager.h"
#include <stdexcept>
#include <vector>


using namespace std;

class CharacterManager
{
	vector<Character> characters;
	Player* player;
	Player* create_player();
public:
	CharacterManager();
	void initialize();
	~CharacterManager();
	Character& get_character(string);
	Player* get_player();
};