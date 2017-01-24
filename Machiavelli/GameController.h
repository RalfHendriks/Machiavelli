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

	const bool HasGameStarted() const;
	const std::shared_ptr<CharacterCard> GetMurderedCharacter() const;
	const std::shared_ptr<CharacterCard> GetRobbedCharacter() const;
private:
	std::shared_ptr<Player> _currentPlayerTurn;
	std::vector<std::shared_ptr<Player>> _currentPlayers;
	std::shared_ptr<CardFactory> _factory;

	std::shared_ptr<CharacterCard> _murdered_character;
	std::shared_ptr<CharacterCard> _robbed_character;

	bool _game_started;
};