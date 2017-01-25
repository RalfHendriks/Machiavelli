#pragma once
#include "Character.h"

class Murderer : public CharacterCard
{
public:
	Murderer(const int id, const std::string name, const CharacterType type);
	~Murderer();

	void Execute(GameController & game_controller) override;

private:
	void PrintCharacterCards(GameController & game_controller) const;
	const CharacterType GetCharacterType(GameController & game_controller, const int index);
};