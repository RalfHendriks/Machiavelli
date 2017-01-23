#pragma once
#include "Character.h"

class ConstructionMaster : public CharacterCard
{
public:
	ConstructionMaster(const int id, const std::string name, const CharacterType type);
	~ConstructionMaster();

	void Execute() override;
private:
};