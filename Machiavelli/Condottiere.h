#pragma once
#include "Character.h"

class Condottiere : public CharacterCard
{
public:
	Condottiere(int ID, CharacterType type);
	~Condottiere();

	void Execute() override;
private:
};