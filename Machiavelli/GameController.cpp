#include "GameController.h"
#include "CardFactory.h"

GameController::GameController()
{
	_factory = std::make_shared<CardFactory>(CardFactory());
	_game_started = false;
	_skip_character_select = false;
	_current_state = GameState::WaitingForPlayers;
}

void GameController::StartGame()
{
	_game_started = true;
	while (_game_started)
	{
		_current_player_turn = _players[0];
		_current_player_turn->SetIsKing(true);

		ResetCards();

	}
	StartCharacterSelect();
}

void GameController::ResetCards()
{
	_character_cards = _factory->GetCharacterCards();
	_building_cards = _factory->GetBuildingCards();
}

void GameController::AddPlayer(std::shared_ptr<Player> player)
{
	_players.push_back(player);
	std::cout << "New player connected: " << player->GetName() << "\r\n";
	std::cout << "Current players in lobby: " << _players.size() << "\r\n";
	if (_players.size() == 2) {
		_players[0]->SendMessageToCLient("Player " + _players[1]->GetName() + " entered the game!\r\n");
		_players[1]->SendMessageToCLient("Player " + _players[0]->GetName() + " entered the game!\r\n");
		StartGame();
	}
}

void GameController::RemovePlayer(std::shared_ptr<Player> player)
{
	_players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
}

void GameController::HandlePlayerInput(std::shared_ptr<Player> player, std::string playerInput)
{
	std::cout << player->GetName() << ": " << playerInput << "\r\n";
	if (playerInput == "skipcharacterselect") _skip_character_select = true;

	player->SetLastPLayerInput(playerInput);
}

void GameController::EndTurn()
{
	_current_player_turn = _current_player_turn == _players[0] ? _players[1] : _players[0];
}

void GameController::StartCharacterSelect()
{

}