#pragma once
#include "Character.h"

class Condottiere : public CharacterCard
{
public:
	Condottiere(int id = 0,CharacterType type = CharacterType::NONE);
	Condottiere();
	~Condottiere();

	void Execute(GameController & game_controller) override;

private:
	void PrintCharacterCards(GameController & game_controller) const;
};