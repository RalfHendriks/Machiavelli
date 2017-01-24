#pragma once
#include "Character.h"

class Preacher : public CharacterCard
{
public:
	Preacher(const int id, const std::string name, const CharacterType type);
	~Preacher();

	void Execute(std::shared_ptr<GameController> game_controller) override;
private:
};