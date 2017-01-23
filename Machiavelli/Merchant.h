#pragma once
#include "Character.h"

class Merchant : public CharacterCard
{
public:
	Merchant(const int id, const std::string name, const CharacterType type);
	~Merchant();

	void Execute() override;
private:
};