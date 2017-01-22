#pragma once
#include "Character.h"

class ConstructionMaster : public CharacterCard
{
public:
	ConstructionMaster(int ID, CharacterType type);
	~ConstructionMaster();

	void Execute() override;
private:
};