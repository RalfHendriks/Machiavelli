#pragma once
#include "Character.h"

class Merchant : public CharacterCard
{
public:
	Merchant(const int id,const CharacterType type);
	Merchant();
	~Merchant();

	void Execute(GameController & game_controller) override;
private:
};