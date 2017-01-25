#pragma once
#include "Character.h"

class King : public CharacterCard
{
public:
	King(const int id, const CharacterType type);
	King();
	~King();

	void Execute(GameController & game_controller) override;
private:
};