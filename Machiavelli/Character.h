#pragma once
#include <string>
#include <iostream>
#include <istream>
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
	const bool IsExecuted() const;
	void SetExecuted(const bool status);
	virtual void Execute(GameController & game_controller) = 0; // Make abstract class

	/*friend std::ostream &operator <<(std::ostream &output, CharacterCard &card);

	friend std::istream &operator >> (std::istream  &input, CharacterCard &card);*/

protected:
	const int _character_id;
	const std::string _name;
	const std::string _description;
	const CharacterType _type;
	bool _executed;
};