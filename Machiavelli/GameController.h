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
	void AddPlayer(std::shared_ptr<Player> player);
	void RemovePlayer(std::shared_ptr<Player> player);
	void HandlePlayerInput(std::shared_ptr<Player> player, std::string playerInput);
	const bool HasGameStarted() const { return _gameStarted; }
private:
	std::shared_ptr<Player> _currentPlayerTurn;
	std::vector<std::shared_ptr<Player>> _currentPlayers;
	std::shared_ptr<CardFactory> _factory;
	bool _gameStarted;
};