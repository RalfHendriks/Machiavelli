#pragma once
#include "Character.h"

class Mage : public CharacterCard
{
public:
	Mage(const int id, const std::string name, const CharacterType type);
	~Mage();

	void Execute(GameController & game_controller) override;
private:
	const void PrintOptions(GameController & game_controller) const;
	void OptionOne(GameController & game_controller);
};