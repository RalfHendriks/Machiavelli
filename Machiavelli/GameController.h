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
	void EndTurn();
	const bool HasGameStarted() const { return _game_started; }
	const GameState GetCurrentState() const { return _current_state; }
private:
	std::shared_ptr<Player> _current_player_turn;
	std::vector<std::shared_ptr<Player>> _players;
	std::shared_ptr<CardFactory> _factory;
	std::vector<std::shared_ptr<BuildingCard>> _building_cards;
	std::vector<std::shared_ptr<CharacterCard>> _character_cards;
	bool _game_started;
	bool _skip_character_select;
	GameState _current_state;
	void StartCharacterSelect();
	int CharacterCardSelect();
	void ResetCards();
	void PlayGame();
	void OutRemainingCharacterCards();
	bool CheckForAllPlayersReady();
	void RemoveCharacterCard(const int index);
};