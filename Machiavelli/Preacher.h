#pragma once
#include "Character.h"

class Preacher : public CharacterCard
{
public:
	Preacher(int ID, CharacterType type);
	~Preacher();

	void Execute() override;
private:
};