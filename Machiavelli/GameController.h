#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Player.h"
#include "CardFactory.h"
#include "CharacterState.h"
#include "Deck.h"

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
	const std::shared_ptr<Player> GetCurrentPlayerTurn() const { return _current_player_turn; }

	const CharacterType GetMurderedCard() const { return _murdered_card; }
	const CharacterType GetRobbedCard() const { return _robbed_card; }

	void SetMurderedCard(CharacterType character_type) { _murdered_card = character_type; }
	void SetRobbedCard(CharacterType character_type) { _robbed_card = character_type; }

	const std::shared_ptr<CardFactory> GetCardFactory() const { return _factory; }
private:
	std::shared_ptr<Player> _current_player_turn;
	std::vector<std::shared_ptr<Player>> _players;

	std::shared_ptr<CardFactory> _factory;
	Deck<std::shared_ptr<BuildingCard>> _building_cards;
	Deck<std::shared_ptr<CharacterCard>> _character_cards;
	CharacterType _murdered_card;
	CharacterType _robbed_card;
	bool _game_started;
	bool _skip_character_select;
	bool _player_builded_building_goal;
	CharacterState _current_state;
	void StartCharacterSelect();
	int CharacterCardSelect();
	int GetPlayerChoice();
	void ResetCards();
	void PlayGame();
	void CheckForGameWinner();
	void SendMessageToOpponent(std::string message);
	void GenerateOptions(int currentChar);
	void OutRemainingCharacterCards();
	bool CheckForAllPlayersReady();
	void RemoveCharacterCard(const int index);
};