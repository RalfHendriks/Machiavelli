#pragma once
#include "Character.h"

class Murderer : public CharacterCard
{
public:
	Murderer(int ID, CharacterType type);
	~Murderer();

	void Execute() override;
private:
};