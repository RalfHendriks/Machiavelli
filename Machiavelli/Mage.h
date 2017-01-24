#pragma once
#include "Character.h"

class Mage : public CharacterCard
{
public:
	Mage(const int id, const std::string name, const CharacterType type);
	~Mage();

	void Execute(std::shared_ptr<GameController> game_controller) override;
private:
};