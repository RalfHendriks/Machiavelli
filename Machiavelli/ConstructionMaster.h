#pragma once
#include "Character.h"

class ConstructionMaster : public CharacterCard
{
public:
	ConstructionMaster(const int id,const CharacterType type);
	ConstructionMaster();
	~ConstructionMaster();

	void Execute(GameController & game_controller) override;
private:
};