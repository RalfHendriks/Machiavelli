#pragma once
#include "Character.h"

class Thief : public CharacterCard
{
public:
	Thief(const int id, const CharacterType type);
	Thief();
	~Thief();

	void Execute(GameController & game_controller) override;

private:
	void PrintCharacterCards(GameController & game_controller) const;
	const CharacterType GetCharacterType(GameController & game_controller, const int index);
};