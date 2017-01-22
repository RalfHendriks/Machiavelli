#pragma once
#include "Character.h"

class King : public CharacterCard
{
public:
	King(int ID, CharacterType type);
	~King();

	void Execute() override;
private:
};