#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Player.h"
#include "CardFactory.h"

class GameController
{
public:
	GameController();

	void StartGame();
	void AddPlayer();
	void RemovePlayer();

private:
	std::vector<std::shared_ptr<Player>> _currentPlayers;
	std::shared_ptr<CardFactory> _factory;
};