#pragma once
#include <string>
#include "CardTypes.h"

class GameController;

class CharacterCard
{
public:

	CharacterCard(const int id, const std::string name, const CharacterType type);
	~CharacterCard();

	const std::string GetName() const;
	const int GetID() const;
	const std::string GetDescription() const;
	const CharacterType GetType() const;

	virtual void Execute(GameController & game_controller) = 0; // Make abstract class

protected:
	const int _character_id;
	const std::string _name;
	const std::string _description;
	const CharacterType _type;
};