#pragma once
#include "Character.h"

class Merchant : public CharacterCard
{
public:
	Merchant(int ID, CharacterType type);
	~Merchant();

	void Execute() override;
private:
};