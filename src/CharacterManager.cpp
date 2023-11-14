#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	//insert enemy characters into the Character array & npcs when Enemy and NPC characters are finished
}

Character& CharacterManager::get_character(string name)
{
	// TODO: make better
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters.at(i).get_name() == name)
		{
			return characters.at(i);
		}
	}
    //if cant find specified character return the static nullCharacter. better than throwing error
	return nullCharacter;
}