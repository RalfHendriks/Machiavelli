#pragma once
#include <iostream>
#include <istream>
#include <string>
#include "CardTypes.h"
using namespace std;

class GameController;

class CharacterCard
{
public:

	//CharacterCard(const int id, const std::string name, const CharacterType type);
	//CharacterCard(int id, std::string name, CharacterType type);
	CharacterCard(int id, CharacterType type);
	CharacterCard();
	~CharacterCard();

	const std::string GetName() const;
	const int GetID() const;
	const std::string GetDescription() const;
	const CharacterType GetType() const;
	const bool IsExecuted() const;
	void SetExecuted(const bool status);
	virtual void Execute(GameController & game_controller); // Make abstract class

	friend std::ostream &operator <<(std::ostream &output, CharacterCard &card);
	friend std::istream &operator >> (std::istream &input, CharacterCard &card);
protected:
	int _character_id;
	std::string _description;
	CharacterType _type;
	bool _executed;
};