#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Player.h"
#include "CardFactory.h"
#include "GameState.h"

class GameController
{
public:
	GameController();

	void StartGame();

	void AddPlayer(std::shared_ptr<Player> player);
	void RemovePlayer(std::shared_ptr<Player> player);
	void HandlePlayerInput(std::shared_ptr<Player> player, std::string playerInput);
	const bool HasGameStarted() const { return _gameStarted; }
	const GameState GetCurrentState() const { return _currentState; }
private:
	std::shared_ptr<Player> _currentPlayerTurn;
	std::vector<std::shared_ptr<Player>> _currentPlayers;
	std::shared_ptr<CardFactory> _factory;
	std::vector<std::shared_ptr<BuildingCard>> _buildingCards;
	std::vector<std::shared_ptr<CharacterCard>> _characterCards;
	bool _gameStarted;
	bool _skipCharacterSelect;
	GameState _currentState;
	void StartCharacterSelect();
	void ResetGame();
};