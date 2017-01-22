#pragma once
#include "Character.h"

class Mage : public CharacterCard
{
public:
	Mage(int ID, CharacterType type);
	~Mage();

	void Execute() override;
private:
};