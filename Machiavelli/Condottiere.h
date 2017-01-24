#pragma once
#include "Character.h"

class Condottiere : public CharacterCard
{
public:
	Condottiere(const int id, const std::string name, const CharacterType type);
	~Condottiere();

	void Execute(std::shared_ptr<GameController> game_controller) override;
private:
};