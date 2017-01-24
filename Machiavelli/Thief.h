#pragma once
#include "Character.h"

class Thief : public CharacterCard
{
public:
	Thief(const int id, const std::string name, const CharacterType type);
	~Thief();

	void Execute(std::shared_ptr<GameController> game_controller) override;
private:
};