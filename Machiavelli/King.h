#pragma once
#include "Character.h"

class King : public CharacterCard
{
public:
	King(const int id, const std::string name, const CharacterType type);
	~King();

	void Execute(std::shared_ptr<GameController> game_controller) override;
private:
};