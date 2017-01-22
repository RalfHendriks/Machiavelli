#pragma once
#include <string>
#include "CardTypes.h"

class CharacterCard
{
public:

	CharacterCard(int id,CharacterType type);
	~CharacterCard();

	std::string GetName() { return CharacterTypeToString(_type); }
	int GetID() { return _characterId; }
	std::string GetDescription() { return _description; }
	CharacterType GetType() { return _type; }

	virtual void Execute() = 0;

protected:
	int _characterId;
	std::string _description;
	CharacterType _type;
};