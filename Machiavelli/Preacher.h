#pragma once
#include "Character.h"

class Preacher : public CharacterCard
{
public:
	Preacher(const int id, const std::string name, const CharacterType type);
	~Preacher();

	void Execute(GameController & game_controller) override;
private:
};