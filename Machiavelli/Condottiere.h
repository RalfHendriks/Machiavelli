#pragma once
#include "Character.h"

class Condottiere : public CharacterCard
{
public:
	Condottiere(int id,CharacterType type);
	Condottiere();
	~Condottiere();

	void Execute(GameController & game_controller) override;

private:
	void PrintCharacterCards(GameController & game_controller) const;
};