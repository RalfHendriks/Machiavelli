#pragma once
#include "Character.h"

class Thief : public CharacterCard
{
public:
	Thief(int ID, CharacterType type);
	~Thief();

	void Execute() override;
private:
};