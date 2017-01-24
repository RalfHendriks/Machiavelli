#pragma once
#include "Character.h"

class ConstructionMaster : public CharacterCard
{
public:
	ConstructionMaster(const int id, const std::string name, const CharacterType type);
	~ConstructionMaster();

	void Execute(std::shared_ptr<GameController> game_controller) override;
private:
};