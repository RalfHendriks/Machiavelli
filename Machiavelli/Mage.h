#pragma once
#include "Character.h"

class Mage : public CharacterCard
{
public:
	Mage(const int id, const std::string name, const CharacterType type);
	~Mage();

	void Execute() override;
private:
};