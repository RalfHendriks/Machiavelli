#pragma once
#include "Character.h"

class Murderer : public CharacterCard
{
public:
	Murderer(const int id, const std::string name, const CharacterType type);
	~Murderer();

	void Execute() override;
private:
};