#pragma once
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "IOManager.h"
#include <vector>


using namespace std;

class CharacterManager
{
	vector<Character> characters;
public:
	CharacterManager();
	Character& get_character(string);
};