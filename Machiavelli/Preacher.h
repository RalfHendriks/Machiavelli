#pragma once
#include "Character.h"

class Preacher : public CharacterCard
{
public:
	Preacher(const int id, const CharacterType type);
	Preacher();
	~Preacher();

	void Execute(GameController & game_controller) override;
private:
};