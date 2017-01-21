#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Player.h"

class GameController
{
public:
	GameController();
	~GameController();

	void StartGame();
	void AddPlayer();
	void RemovePlayer();

private:
	std::vector<std::shared_ptr<Player>> currentPlayers;
};